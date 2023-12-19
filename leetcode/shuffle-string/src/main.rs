// https://leetcode.cn/problems/shuffle-string

pub struct Solution {}
impl Solution {
    pub fn restore_string(s: String, indices: Vec<i32>) -> String {
        let mut a = s.chars().zip(indices.into_iter()).collect::<Vec<_>>();
        a.sort_unstable_by_key(|&(_, i)| i);
        a.into_iter().map(|(c, _)| c).collect()
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_restore_string() {
        // Test case 1
        let s1 = String::from("codeleet");
        let indices1 = vec![4, 5, 6, 7, 0, 2, 1, 3];
        let expected1 = String::from("leetcode");
        assert_eq!(Solution::restore_string(s1, indices1), expected1);

        // Test case 2
        let s2 = String::from("abc");
        let indices2 = vec![0, 1, 2];
        let expected2 = String::from("abc");
        assert_eq!(Solution::restore_string(s2, indices2), expected2);

        // Test case 3
        let s3 = String::from("aiohn");
        let indices3 = vec![3, 1, 4, 2, 0];
        let expected3 = String::from("nihao");
        assert_eq!(Solution::restore_string(s3, indices3), expected3);
    }
}