#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "https://leetcode-cn.com/problems/find-median-from-data-stream/"
import heapq as hq


class MedianFinder(object):

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.left = []
        self.right = []
        self.median = 0

    def addNum(self, num):
        """
        :type num: int
        :rtype: None
        """
        if num > self.median:
            hq.heappush(self.right, num)
        else:
            hq.heappush(self.left, -num)

        if len(self.left) - len(self.right) > 1:
            hq.heappush(self.right, -hq.heappop(self.left))
        elif len(self.right) - len(self.left) > 1:
            hq.heappush(self.left, -hq.heappop(self.right))
        else:
            pass

        if len(self.left) > len(self.right):
            self.median = -self.left[0]
        elif len(self.left) < len(self.right):
            self.median = self.right[0]
        else:
            self.median = (self.right[0] - self.left[0])/2

    def findMedian(self):
        """
        :rtype: float
        """
        return self.median


def main():
    pass


if __name__ == '__main__':
    main()
