#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

# 返回这三个数的和。

# 假定每组输入只存在恰好一个解。


# 示例 1：

# 输入：nums = [-1,2,1,-4], target = 1
# 输出：2
# 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
# 示例 2：

# 输入：nums = [0,0,0], target = 1
# 输出：0


# 提示：

# 3 <= nums.length <= 1000
# -1000 <= nums[i] <= 1000
# -104 <= target <= 104

from typing import List


class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        nums.sort()
        res = nums[0] + nums[1] + nums[2]
        for i in range(len(nums) - 2):
            left, right = i + 1, len(nums) - 1
            while left < right:
                sum = nums[i] + nums[left] + nums[right]
                res = sum if abs(sum - target) < abs(res - target) else res
                if sum == target:
                    return sum
                elif sum < target:
                    left += 1
                else:
                    right -= 1
        return res


def main():
    print(Solution().threeSumClosest([2, 3, 8, 9, 10], 16))


if __name__ == "__main__":
    main()
