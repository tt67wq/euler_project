// https://leetcode.cn/problems/check-if-all-the-integers-in-a-range-are-covered/

// 给你一个二维整数数组 ranges 和两个整数 left 和 right 。每个 ranges[i] = [starti, endi] 表示一个从 starti 到 endi 的 闭区间 。

// 如果闭区间 [left, right] 内每个整数都被 ranges 中 至少一个 区间覆盖，那么请你返回 true ，否则返回 false 。

// 已知区间 ranges[i] = [starti, endi] ，如果整数 x 满足 starti <= x <= endi ，那么我们称整数x 被覆盖了。

// 示例 1：

// 输入：ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
// 输出：true
// 解释：2 到 5 的每个整数都被覆盖了：
// - 2 被第一个区间覆盖。
// - 3 和 4 被第二个区间覆盖。
// - 5 被第三个区间覆盖。
// 示例 2：

// 输入：ranges = [[1,10],[10,20]], left = 21, right = 21
// 输出：false
// 解释：21 没有被任何一个区间覆盖。

pub struct Solution {}

impl Solution {
    pub fn is_covered(ranges: Vec<Vec<i32>>, left: i32, right: i32) -> bool {
        let mut flags = vec![false; 51];

        for range in ranges {
            let l = range[0].max(left) as usize;
            let r = range[1].min(right) as usize;
            for i in l..=r {
                flags[i] = true;
            }
        }

        for i in left as usize..=right as usize {
            if !flags[i] {
                return false;
            }
        }
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_covered() {
        let ranges = vec![vec![1, 3], vec![5, 7], vec![9, 11]];
        assert_eq!(Solution::is_covered(ranges, 2, 6), false);

        let ranges = vec![vec![1, 10], vec![10, 20]];
        assert_eq!(Solution::is_covered(ranges, 21, 21), false);

        let ranges = vec![vec![1, 2], vec![3, 4], vec![5, 6]];
        assert_eq!(Solution::is_covered(ranges, 2, 5), true);

        let ranges = vec![vec![1, 50]];
        assert_eq!(Solution::is_covered(ranges, 1, 50), true);
    }
}
