// https://leetcode.cn/problems/xoh6Oh/
pub struct Solution {}
impl Solution {
    pub fn divide(a: i32, b: i32) -> i32 {
        if a == 0 {
            return 0;
        }

        if b == 1 {
            return a;
        }

        if a == i32::min_value() && b == -1 {
            return i32::max_value();
        }

        let mut ans = 0;
        let sign = a.signum() * b.signum();
        let (mut a, b) = ((a as i64).abs(), (b as i64).abs());

        while a >= b {
            // d表示a/b的二进制位数
            let mut d = b.leading_zeros() - a.leading_zeros();
            if d == 0 {
                // 如果a和b的位数相同，那么a/b=1
                ans += 1;
                break;
            }
            // a < b << d，说明a/b的位数不够，需要减小d
            if a < b << d {
                d -= 1;
            }
            // a -= b << d，相当于a -= b * 2^d
            a -= b << d;
            ans += 2i32.pow(d);
        }
        ans * sign
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_divide() {
        assert_eq!(Solution::divide(10, 2), 5);
        assert_eq!(Solution::divide(-10, 2), -5);
        assert_eq!(Solution::divide(10, -2), -5);
        assert_eq!(Solution::divide(-10, -2), 5);
        assert_eq!(Solution::divide(0, 1), 0);
        assert_eq!(Solution::divide(1, 1), 1);
        assert_eq!(Solution::divide(i32::min_value(), -1), i32::max_value());
        assert_eq!(Solution::divide(i32::max_value(), 1), i32::max_value());
        assert_eq!(Solution::divide(i32::min_value(), 1), i32::min_value());
    }
}
