// https://leetcode.cn/problems/delete-characters-to-make-fancy-string/
pub struct Solution {}

impl Solution {
    pub fn make_fancy_string(s: String) -> String {
        if s.len() < 3 {
            return s;
        }
        let mut res = String::with_capacity(s.len());
        let b = s.as_bytes();
        for a in b.windows(3) {
            if a[0] != a[1] || a[1] != a[2] {
                res.push(a[0] as char);
            }
        }
        res.push(b[s.len() - 2] as char);
        res.push(b[s.len() - 1] as char);
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_make_fancy_string_empty() {
        let s = String::from("");
        assert_eq!(Solution::make_fancy_string(s), "");
    }

    #[test]
    fn test_make_fancy_string_single_char() {
        let s = String::from("a");
        assert_eq!(Solution::make_fancy_string(s), "a");
    }

    #[test]
    fn test_make_fancy_string_two_chars() {
        let s = String::from("ab");
        assert_eq!(Solution::make_fancy_string(s), "ab");
    }

    #[test]
    fn test_make_fancy_string_no_repeated_chars() {
        let s = String::from("abcde");
        assert_eq!(Solution::make_fancy_string(s), "abcde");
    }

    #[test]
    fn test_make_fancy_string_repeated_chars() {
        let s = String::from("aaabbbccc");
        assert_eq!(Solution::make_fancy_string(s), "aabbcc");
    }

    #[test]
    fn test_make_fancy_string_repeated_chars_at_end() {
        let s = String::from("abcdddeeefff");
        assert_eq!(Solution::make_fancy_string(s), "abcddeeff");
    }
}
