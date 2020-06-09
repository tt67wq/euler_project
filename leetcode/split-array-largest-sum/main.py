#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def splitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        # max(nums), sum(nums)
        if len(nums) == m:
            return max(nums)

        lo, hi = max(nums), sum(nums)
        while lo < hi:
            mid = (lo + hi) // 2  # 最大和

            # ------以下在模拟划分子数组的过程
            temp, cnt = 0, 1
            for num in nums:
                temp += num
                # cnt += 1
                if temp > mid:  # 说明当前这个子数组的和已经超过了允许的最大值mid，需要把当前元素放在下一个子数组里
                    temp = num
                    cnt += 1
            # print temp, cnt, mid
            # ------以上在模拟划分子数组的过程

            if cnt > m:  # 说明分出了比要求多的子数组，多切了几刀，说明mid应该加大，这样能使子数组的个数减少
                lo = mid + 1
            elif cnt <= m:
                hi = mid

        return lo


def main():
    pass


if __name__ == "__main__":
    main()
