// https://leetcode.cn/problems/max-pair-sum-in-an-array/

// 给你一个下标从 0 开始的整数数组 nums 。请你从 nums 中找出和 最大 的一对数，且这两个数数位上最大的数字相等。

// 返回最大和，如果不存在满足题意的数字对，返回 -1 。

// 示例 1：

// 输入：nums = [51,71,17,24,42]
// 输出：88
// 解释：
// i = 1 和 j = 2 ，nums[i] 和 nums[j] 数位上最大的数字相等，且这一对的总和 71 + 17 = 88 。
// i = 3 和 j = 4 ，nums[i] 和 nums[j] 数位上最大的数字相等，且这一对的总和 24 + 42 = 66 。
// 可以证明不存在其他数对满足数位上最大的数字相等，所以答案是 88 。
// 示例 2：

// 输入：nums = [1,2,3,4]
// 输出：-1
// 解释：不存在数对满足数位上最大的数字相等。

// 提示：

// 2 <= nums.length <= 100
// 1 <= nums[i] <= 104

use std::collections::HashMap;

pub struct Solution {}

impl Solution {
    pub fn max_sum(nums: Vec<i32>) -> i32 {
        let mut map: HashMap<char, Vec<i32>> = HashMap::new();

        for num in nums {
            if let Some(max_sum) = num.to_string().chars().max() {
                map.entry(max_sum)
                    .and_modify(|v| v.push(num))
                    .or_insert(vec![num]);
            }
        }

        let mut ans: i32 = -1;
        for v in map.values_mut() {
            if v.len() < 2 {
                continue;
            }
            v.sort();
            let last2_sum: i32 = *&v[v.len() - 2..].iter().sum();
            ans = ans.max(last2_sum);
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_sum() {
        // Test case 1
        let nums1 = vec![1, 2, 3, 4, 5];
        assert_eq!(Solution::max_sum(nums1), -1);

        // Test case 2
        let nums2 = vec![9, 8, 7, 6, 5];
        assert_eq!(Solution::max_sum(nums2), -1);

        // Test case 3
        let nums3 = vec![5, 5, 5, 5, 5];
        assert_eq!(Solution::max_sum(nums3), 10);

        // Test case 4
        let nums4 = vec![1, 10, 100, 1000, 10000];
        assert_eq!(Solution::max_sum(nums4), 11000);

        // Test case 5
        let nums5 = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
        assert_eq!(Solution::max_sum(nums5), 11);
    }
}
