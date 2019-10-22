#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

# 执行用时 :
# 68 ms
# 内存消耗 :
# 12.4 MB

import heapq as hq


class Solution:
    def findKthLargest(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        h = []

        for num in nums:
            if len(h) < k:
                hq.heappush(h, num)
            else:
                t1 = h[0]
                if num > t1:
                    hq.heappop(h)
                    hq.heappush(h, num)

        print(h)
        return h[0]


def main():
    s = Solution()
    print(s.findKthLargest([3, 2, 1, 5, 6, 4], 2))
    print(s.findKthLargest([3, 2, 3, 1, 2, 4, 5, 5, 6], 4))


if __name__ == '__main__':
    main()
