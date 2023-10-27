// https://leetcode.cn/problems/fibonacci-number/

pub struct Solution {}

impl Solution {
    pub fn fib(n: i32) -> i32 {
        if n == 0 {
            return 0;
        }
        let mut prev = 0;
        let mut curr = 1;

        for _ in 0..n - 1 {
            let tmp = curr;
            curr = prev + curr;
            prev = tmp;
        }
        curr
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_fib() {
        assert_eq!(Solution::fib(0), 0);
        assert_eq!(Solution::fib(1), 1);
        assert_eq!(Solution::fib(2), 1);
        assert_eq!(Solution::fib(3), 2);
        assert_eq!(Solution::fib(4), 3);
        assert_eq!(Solution::fib(5), 5);
        assert_eq!(Solution::fib(6), 8);
        assert_eq!(Solution::fib(7), 13);
        assert_eq!(Solution::fib(8), 21);
        assert_eq!(Solution::fib(9), 34);
        assert_eq!(Solution::fib(10), 55);
    }
}
