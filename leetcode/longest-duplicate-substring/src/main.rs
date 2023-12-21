// https://leetcode.cn/problems/longest-duplicate-substring/

// 给你一个字符串 s ，考虑其所有重复子串：即 s 的（连续）子串，在 s 中出现 2 次或更多次。这些出现之间可能存在重叠。
// 返回任意一个可能具有最长长度的重复子串。如果s不含重复子串，那么答案为"" 。

// 示例 1：
// 输入：s = "banana"
// 输出："ana"

// 示例 2：
// 输入：s = "abcd"
// 输出：""

// 提示：
// 2 <= s.length <= 3 * 104
// s 由小写英文字母组成

use std::collections::HashMap;
pub struct Solution {}
impl Solution {
    pub fn longest_dup_substring(s: String) -> String {
        let mut l = 0;
        let mut r = s.len() - 1;
        while l < r {
            let m = l + ((r - l + 1) >> 1);
            if Solution::find_duplicate(&s, m).is_some() {
                l = m;
            } else {
                r = m - 1;
            }
        }
        Solution::find_duplicate(&s, l).unwrap_or("".to_string())
    }

    pub fn find_duplicate(s: &String, length: usize) -> Option<String> {
        if length == 0 {
            return Some("".to_string());
        }
        let mut hash: u64 = 0;
        let prime = 29;
        let mut first_entry_power = 1;
        let mut set: HashMap<u64, usize> = HashMap::new();

        let s_arr = s.as_bytes();

        // rabin-karp
        for i in 0..length {
            first_entry_power *= prime;
            hash = hash * prime + (s_arr[i] - b'a') as u64;
        }

        set.insert(hash, 0);
        for i in length..s.len() {
            hash = hash * prime + (s_arr[i] - b'a') as u64
                - first_entry_power * (s_arr[i - length] - b'a') as u64;
            if set.contains_key(&hash) {
                let idx = *set.get(&hash).unwrap();
                return Some(s[idx..idx + length].to_string());
            }
            set.insert(hash, i - length + 1);
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_longest_dup_substring() {
        // Test case 1: Duplicate substring exists
        let s = String::from("banana");
        let result = Solution::longest_dup_substring(s);
        assert_eq!(result, "ana");

        // Test case 2: Duplicate substring does not exist
        let s = String::from("abcdefg");
        let result = Solution::longest_dup_substring(s);
        assert_eq!(result, "");
    }
}
