// https://leetcode.cn/problems/second-largest-digit-in-a-string/description/

// 给你一个混合字符串 s ，请你返回 s 中 第二大 的数字，如果不存在第二大的数字，请你返回 -1 。

// 混合字符串 由小写英文字母和数字组成。

// 示例 1：

// 输入：s = "dfa12321afd"
// 输出：2
// 解释：出现在 s 中的数字包括 [1, 2, 3] 。第二大的数字是 2 。
// 示例 2：

// 输入：s = "abc1111"
// 输出：-1
// 解释：出现在 s 中的数字只包含 [1] 。没有第二大的数字。

// 提示：

// 1 <= s.length <= 500
// s 只包含小写英文字母和（或）数字。

pub struct Solution {}

use std::collections::HashSet;

impl Solution {
    pub fn second_highest(s: String) -> i32 {
        let mut vec = Vec::new();
        let mut hs = HashSet::new();

        for c in s.chars() {
            if c.is_digit(10) {
                let n = c.to_digit(10).unwrap();
                if !hs.contains(&n) {
                    hs.insert(n);
                    vec.push(n);
                }
            }
        }
        if vec.len() < 2 {
            return -1;
        }

        vec.sort();
        vec[vec.len() - 2] as i32
    }
}
