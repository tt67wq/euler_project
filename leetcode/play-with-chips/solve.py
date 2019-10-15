#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "https://leetcode-cn.com/problems/play-with-chips/"


class Solution:
    def minCostToMoveChips(self, chips):
        mp = {0: 0, 1: 0}
        for c in chips:
            mp[c % 2] += 1
        return min(list(mp.values()))


def main():
    s = Solution()
    while 1:
        print(s.minCostToMoveChips([int(x) for x in input().split(",")]))


if __name__ == '__main__':
    main()
