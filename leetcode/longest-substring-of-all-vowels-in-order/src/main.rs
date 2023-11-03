// https://leetcode.cn/problems/longest-substring-of-all-vowels-in-order/

// 当一个字符串满足如下条件时，我们称它是 美丽的 ：

// 所有 5 个英文元音字母（'a' ，'e' ，'i' ，'o' ，'u'）都必须 至少 出现一次。
// 这些元音字母的顺序都必须按照 字典序 升序排布（也就是说所有的 'a' 都在 'e' 前面，所有的 'e' 都在 'i' 前面，以此类推）
// 比方说，字符串 "aeiou" 和 "aaaaaaeiiiioou" 都是 美丽的 ，但是 "uaeio" ，"aeoiu" 和 "aaaeeeooo" 不是美丽的 。

// 给你一个只包含英文元音字母的字符串 word ，请你返回 word 中 最长美丽子字符串的长度 。如果不存在这样的子字符串，请返回 0 。

// 子字符串 是字符串中一个连续的字符序列。

pub struct Solution {}

impl Solution {
    fn index(c: char) -> i32 {
        match c {
            'a' => 1,
            'e' => 2,
            'i' => 3,
            'o' => 4,
            'u' => 5,
            _ => 0,
        }
    }
    pub fn longest_beautiful_substring(word: String) -> i32 {
        if word.len() < 5 {
            return 0;
        }
        let word = word.chars().collect::<Vec<char>>();
        let (mut i, mut j) = (0i32, -1i32);
        let mut res = 0;

        while j < word.len() as i32 - 1 {
            j += 1;
            if j - i + 1 == 1 {
                // 第一个字符
            } else if Self::index(word[j as usize]) - Self::index(word[j as usize - 1]) == 0
                || Self::index(word[j as usize]) - Self::index(word[j as usize - 1]) == 1
            {
                // 与前一个字符相同或者比前一个字符大1
            } else {
                // 不满足条件
                i = j;
            }

            if word[i as usize] != 'a' {
                // 不是以a开头
                i += 1;
            } else if word[j as usize] == 'u' {
                // 以u结尾
                res = res.max(j - i + 1);
            }
        }
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_empty_string() {
        assert_eq!(Solution::longest_beautiful_substring("".to_string()), 0);
    }

    #[test]
    fn test_string_shorter_than_5() {
        assert_eq!(Solution::longest_beautiful_substring("abc".to_string()), 0);
    }

    #[test]
    fn test_string_without_u() {
        assert_eq!(
            Solution::longest_beautiful_substring("abacadae".to_string()),
            0
        );
    }

    #[test]
    fn test_string_with_single_character() {
        assert_eq!(
            Solution::longest_beautiful_substring("aueio".to_string()),
            0
        );
    }

    #[test]
    fn test_string_with_multiple_beautiful_substrings() {
        assert_eq!(
            Solution::longest_beautiful_substring("aeiaaioaaaaeiiiiouuuooaauuaeiu".to_string()),
            13
        );
    }

    #[test]
    fn test_string_with_non_beautiful_substrings() {
        assert_eq!(
            Solution::longest_beautiful_substring("aeeeiiiioooauuuaeiou".to_string()),
            5
        );
    }
}
