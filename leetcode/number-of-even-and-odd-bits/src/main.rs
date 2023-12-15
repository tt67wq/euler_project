// https://leetcode.cn/problems/number-of-even-and-odd-bits/description/

pub struct Solution {}
impl Solution {
    pub fn even_odd_bit(n: i32) -> Vec<i32> {
        let mut even: i32 = 0;
        let mut odd: i32 = 0;

        for index in 0..30 {
            if n & (1 << index) != 0 {
                if index % 2 == 0 {
                    even += 1;
                } else {
                    odd += 1;
                }
            }
        }

        vec![even, odd]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_even_odd_bit() {
        // Test case 1: n = 2
        // Binary representation: 10
        // Even bits: 1 (index 1)
        // Odd bits: 0
        assert_eq!(Solution::even_odd_bit(17), vec![2, 0]);

        // Test case 2: n = 5
        // Binary representation: 101
        // Even bits: 1 (index 0)
        // Odd bits: 2 (index 2, 1)
        assert_eq!(Solution::even_odd_bit(2), vec![0, 1]);
    }
}
