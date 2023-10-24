#!/usr/bin/env python
# -*- coding: utf-8 -*-

from typing import Counter, List
import math


class Solution:
    def minGroupsForValidAssignment(self, nums: List[int]) -> int:
        cnt = Counter(nums)
        ans = math.inf

        for i in range(1, min(cnt.values()) + 2):
            res = 0
            for x in cnt.values():
                # 贪心
                v = (x + i - 1) // i
                k1 = x - v * (i - 1)
                k2 = v - k1
                if k1 < 0 or k2 < 0:
                    break
                res += v
            else:
                ans = min(ans, res)
        return ans


def main():
    pass


if __name__ == "__main__":
    main()
