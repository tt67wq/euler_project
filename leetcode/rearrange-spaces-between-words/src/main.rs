// https://leetcode.com/problems/rearrange-spaces-between-words/

// 给你一个字符串 text ，该字符串由若干被空格包围的单词组成。每个单词由一个或者多个小写英文字母组成，并且两个单词之间至少存在一个空格。
// 题目测试用例保证 text 至少包含一个单词 。

// 请你重新排列空格，使每对相邻单词之间的空格数目都 相等 ，并尽可能 最大化 该数目。如果不能重新平均分配所有空格，
// 请将多余的空格放置在字符串末尾 ，这也意味着返回的字符串应当与原 text 字符串的长度相等。

// 返回 重新排列空格后的字符串 。
pub struct Solution {}
impl Solution {
    pub fn reorder_spaces(text: String) -> String {
        let spaces = text.chars().filter(|&c| c == ' ').count(); // 空格数
        let words: Vec<&str> = text.split_whitespace().collect(); // 单词数组

        if words.len() == 1 {
            return words[0].to_string() + &" ".repeat(spaces);
        }

        let mut ans = String::new();
        let space = spaces / (words.len() - 1); // 每个单词之间的空格数
        let extra = spaces % (words.len() - 1); // 多余的空格数

        for i in 0..words.len() {
            ans += &words[i];
            if i != words.len() - 1 {
                ans += &" ".repeat(space);
            } else {
                ans += &" ".repeat(extra);
            }
        }

        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_reorder_spaces_single_word() {
        let input = "word    ".to_string();
        let output = Solution::reorder_spaces(input);
        assert_eq!(output, "word    ".to_string());
    }

    #[test]
    fn test_reorder_spaces_multiple_words() {
        let input = "  this   is  a sentence ".to_string();
        let output = Solution::reorder_spaces(input);
        assert_eq!(output, "this   is   a   sentence".to_string());
    }

    #[test]
    fn test_reorder_spaces_no_extra_spaces() {
        let input = "no extra spaces".to_string();
        let output = Solution::reorder_spaces(input);
        assert_eq!(output, "no extra spaces".to_string());
    }

    #[test]
    fn test_reorder_spaces_with_extra_spaces() {
        let input = "  walks  udp package   into  bar a".to_string();
        let output = Solution::reorder_spaces(input);
        assert_eq!(output, "walks  udp  package  into  bar  a ".to_string());
    }
}
