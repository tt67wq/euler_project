pub struct Solution {}

impl Solution {
    pub fn sum_odd_length_subarrays(arr: Vec<i32>) -> i32 {
        let n = arr.len();
        let mut pre_sum = vec![0; n + 1];
        for i in 0..n {
            pre_sum[i + 1] = pre_sum[i] + arr[i];
        }

        let mut ans = 0;

        for i in 0..n {
            let mut j = 1;
            while i + j <= n {
                ans += pre_sum[i + j] - pre_sum[i];
                j += 2;
            }
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sum_odd_length_subarrays() {
        // Test case 1
        let arr1 = vec![1, 4, 2, 5, 3];
        let result1 = Solution::sum_odd_length_subarrays(arr1);
        assert_eq!(result1, 58);

        // Test case 2
        let arr2 = vec![1, 2];
        let result2 = Solution::sum_odd_length_subarrays(arr2);
        assert_eq!(result2, 3);

        // Test case 3
        let arr3 = vec![10, 11, 12];
        let result3 = Solution::sum_odd_length_subarrays(arr3);
        assert_eq!(result3, 66);

        // Test case 4
        let arr4 = vec![1];
        let result4 = Solution::sum_odd_length_subarrays(arr4);
        assert_eq!(result4, 1);
    }
}
