// https://leetcode.cn/problems/remove-boxes/
pub struct Solution {}

impl Solution {
    pub fn remove_boxes(boxes: Vec<i32>) -> i32 {
        let mut dp = [[[0; 100]; 100]; 100];
        Self::calculate_score(&boxes, &mut dp, 0, boxes.len() - 1, 0) as i32
    }

    fn calculate_score(
        boxes: &[i32],
        dp: &mut [[[u16; 100]; 100]; 100],
        l: usize,
        mut r: usize,
        mut k: usize,
    ) -> u16 {
        if l as isize > r as isize {
            return 0;
        }
        if dp[l][r][k] != 0 {
            return dp[l][r][k];
        }

        while l < r && boxes[r] == boxes[r - 1] {
            r -= 1;
            k += 1;
        }

        dp[l][r][k] = Self::calculate_score(boxes, dp, l, r.wrapping_sub(1), 0)
            + (k as u16 + 1) * (k as u16 + 1);

        for i in l..r {
            if boxes[i] == boxes[r] {
                dp[l][r][k] = std::cmp::max(
                    dp[l][r][k],
                    Self::calculate_score(boxes, dp, l, i, k + 1)
                        + Self::calculate_score(boxes, dp, i + 1, r - 1, 0),
                );
            }
        }
        dp[l][r][k]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_remove_boxes() {
        let test_cases = vec![
            (vec![1, 3, 2, 2, 2, 3, 4, 3, 1], 23),
            (vec![1, 1, 1], 9),
            (vec![1], 1),
            (vec![1, 2, 3, 4, 5], 5),
            (vec![1, 2, 2, 2, 1], 13),
        ];

        for (input, expected) in test_cases {
            let result = Solution::remove_boxes(input.clone());
            assert_eq!(result, expected, "Failed on input: {:?}", input);
        }
    }
}
