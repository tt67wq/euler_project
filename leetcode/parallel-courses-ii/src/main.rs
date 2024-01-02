// https://leetcode.cn/problems/parallel-courses-ii/

// 给你一个整数 n 表示某所大学里课程的数目，编号为 1 到 n ，数组 relations 中，
// relations[i] = [xi, yi]  表示一个先修课的关系，也就是课程 xi 必须在课程 yi 之前上。同时你还有一个整数 k 。

// 在一个学期中，你 最多 可以同时上 k 门课，前提是这些课的先修课在之前的学期里已经上过了。

// 请你返回上完所有课最少需要多少个学期。题目保证一定存在一种上完所有课的方式。

pub struct Solution {}
impl Solution {
    // 计算一个数的二进制表示中 1 的个数
    pub fn bit_cnt(mut v: i32) -> i32 {
        let mut cnt = 0;

        while v != 0 {
            v &= (v - 1);
            cnt += 1;
        }
        cnt
    }
    pub fn min_number_of_semesters(n: i32, relations: Vec<Vec<i32>>, k: i32) -> i32 {
        let mut dp = vec![i32::MAX; 1 << n]; // dp[i] 表示上完 i 这些课需要的最少学期数
        let mut need = vec![0; 1 << n]; // need[i] 表示 i 这个集合中所有课程的先修课

        for r in relations.iter() {
            // need[r[1]] |= r[0] 表示 r[1] 这门课需要先修 r[0] 这门课
            need[1 << (r[1] - 1) as usize] |= 1 << (r[0] - 1) as usize;
        }

        dp[0] = 0;

        for i in 1..(1 << n) {
            // i & (i-1) 会把 i 的最后一个 1 变成 0
            // i & (-i) 会把 i 的最后一个 1 保留，其它位变成 0
            // need[i] 表示 i 这个集合中所有课程的先修课
            need[i as usize] = need[(i & (i - 1)) as usize] | need[(i & (-i)) as usize];

            if (need[i as usize] | i) != i {
                continue;
            }

            // v表示 i 的补集, 即 i 中后修课的集合
            // i ^ v = need[i]
            let v = i as i32 ^ need[i as usize];

            // 后修课小于k，可以在一个学期内上完
            if Solution::bit_cnt(v) <= k {
                dp[i as usize] = dp[i as usize].min(dp[(i ^ v) as usize] + 1);
            } else {
                // 一个学期内上不完，需要多个学期
                let mut u = v;
                // 枚举 v 的所有子集, 即枚举所有的上课方式
                while u != 0 {
                    if Solution::bit_cnt(u) <= k {
                        dp[i as usize] = dp[i as usize].min(dp[(i ^ u) as usize] + 1);
                    }
                    u = (u - 1) & v;
                }
            }
        }

        dp[(1 << n) - 1]
    }
}
