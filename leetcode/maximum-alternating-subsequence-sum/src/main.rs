// https://leetcode.cn/problems/maximum-alternating-subsequence-sum/

// 一个下标从 0 开始的数组的 交替和 定义为 偶数 下标处元素之 和 减去 奇数 下标处元素之 和 。

// 比方说，数组 [4,2,5,3] 的交替和为 (4 + 5) - (2 + 3) = 4 。
// 给你一个数组 nums ，请你返回 nums 中任意子序列的 最大交替和 （子序列的下标 重新 从 0 开始编号）。

// 一个数组的 子序列 是从原数组中删除一些元素后（也可能一个也不删除）剩余元素不改变顺序组成的数组。
// 比方说，[2,7,4] 是 [4,2,3,7,2,1,4] 的一个子序列（加粗元素），但是 [2,4,2] 不是。

pub struct Solution {}

impl Solution {
    pub fn max_alternating_sum(nums: Vec<i32>) -> i64 {
        let n = nums.len();
        let mut dp1 = vec![0; n + 1];
        let mut dp2 = vec![0; n + 1];

        for i in 1..=n {
            dp1[i] = (dp2[i - 1] + nums[i - 1] as i64).max(dp1[i - 1]);
            dp2[i] = (dp1[i - 1] - nums[i - 1] as i64).max(dp2[i - 1]);
        }

        dp1[n].max(dp2[n])
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_alternating_sum() {
        // Test case 1
        let nums1 = vec![4, 2, 5, 3];
        let result1 = Solution::max_alternating_sum(nums1);
        assert_eq!(result1, 7);

        // Test case 2
        let nums2 = vec![5, 6, 7, 8];
        let result2 = Solution::max_alternating_sum(nums2);
        assert_eq!(result2, 8);

        // Test case 3
        let nums3 = vec![6, 2, 1, 2, 4, 5];
        let result3 = Solution::max_alternating_sum(nums3);
        assert_eq!(result3, 10);
    }
}
