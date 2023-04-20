#!/usr/bin/env python
# -*- coding: utf-8 -*-
from typing import List

# 给你两个整数数组 arr1 和 arr2，返回使 arr1 严格递增所需要的最小「操作」数（可能为 0）。

# 每一步「操作」中，你可以分别从 arr1 和 arr2 中各选出一个索引，分别为 i 和 j，0 <= i < arr1.length 和 0 <= j < arr2.length，然后进行赋值运算 arr1[i] = arr2[j]。

# 如果无法让 arr1 严格递增，请返回 -1。


# 示例 1：

# 输入：arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
# 输出：1
# 解释：用 2 来替换 5，之后 arr1 = [1, 2, 3, 6, 7]。
# 示例 2：

# 输入：arr1 = [1,5,3,6,7], arr2 = [4,3,1]
# 输出：2
# 解释：用 3 来替换 5，然后用 4 来替换 3，得到 arr1 = [1, 3, 4, 6, 7]。
# 示例 3：

# 输入：arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
# 输出：-1
# 解释：无法使 arr1 严格递增。
import bisect


class Solution:
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:
        # 去重,排序
        arr2 = sorted(set(arr2))
        n, m = len(arr1), len(arr2)
        # dp[i][j] => arr1[:i]进行j次替换后的arr1[i-1]的最小值
        dp = [[float("inf")] * (min(m, n) + 1) for _ in range(n + 1)]
        dp[0][0] = -1
        for i in range(1, n + 1):
            for j in range(min(i, m) + 1):
                if arr1[i - 1] > dp[i - 1][j]:
                    dp[i][j] = arr1[i - 1]
                if j > 0 and dp[i - 1][j - 1] != float("inf"):
                    idx = bisect.bisect_right(arr2, dp[i - 1][j - 1], j - 1)
                    if idx < m:
                        dp[i][j] = min(dp[i][j], arr2[idx])
                if i == n and dp[i][j] != float("inf"):
                    return j
        return -1


def main():
    print(Solution().makeArrayIncreasing([1, 5, 3, 6, 7], [1, 3, 2, 4]))
    print(Solution().makeArrayIncreasing([1, 5, 3, 6, 7], [4, 3, 1]))
    print(Solution().makeArrayIncreasing([1, 5, 3, 6, 7], [1, 6, 3, 3]))


if __name__ == "__main__":
    main()
