// https://leetcode.cn/problems/dKk3P7/

// 给定两个字符串 s 和 t ，编写一个函数来判断它们是不是一组变位词（字母异位词）。

// 注意：若 s 和 t 中每个字符出现的次数都相同且字符顺序不完全相同，则称 s 和 t 互为变位词（字母异位词）。

// 示例 1:

// 输入: s = "anagram", t = "nagaram"
// 输出: true
// 示例 2:

// 输入: s = "rat", t = "car"
// 输出: false
// 示例 3:

// 输入: s = "a", t = "a"
// 输出: false

pub struct Solution {}

impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        if s == t {
            return false;
        }

        let mut last: [i32; 26] = [0; 26];
        for c in s.chars() {
            last[c as usize - 'a' as usize] += 1;
        }
        for c in t.chars() {
            last[c as usize - 'a' as usize] -= 1;
        }
        for i in 0..26 {
            if last[i] != 0 {
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
    fn test_is_anagram() {
        assert_eq!(
            Solution::is_anagram("anagram".to_string(), "nagaram".to_string()),
            true
        );
        assert_eq!(
            Solution::is_anagram("rat".to_string(), "car".to_string()),
            false
        );
        assert_eq!(
            Solution::is_anagram("hello".to_string(), "world".to_string()),
            false
        );
        assert_eq!(
            Solution::is_anagram("a".to_string(), "a".to_string()),
            false
        );
        assert_eq!(
            Solution::is_anagram("ab".to_string(), "ba".to_string()),
            true
        );
    }
}
