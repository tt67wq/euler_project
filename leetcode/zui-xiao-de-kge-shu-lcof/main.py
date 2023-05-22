#!/usr/bin/env python
# -*- coding: utf-8 -*-

from typing import List
import heapq


class MinHeap:
    def __init__(self):
        self.heap = []

    def push(self, item):
        heapq.heappush(self.heap, item)

    def pop(self):
        return heapq.heappop(self.heap)

    def peek(self):
        return self.heap[0] if self.heap else None

    def size(self):
        return len(self.heap)


class Solution:
    """
    https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/
    """

    def getLeastNumbers(self, arr: List[int], k: int) -> List[int]:
        hp = MinHeap()
        for i in arr:
            hp.push(i)
        res = []
        for i in range(k):
            res.append(hp.pop())
        return res


def main():
    pass


if __name__ == "__main__":
    main()
