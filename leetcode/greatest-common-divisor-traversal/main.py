#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/greatest-common-divisor-traversal/

from typing import List


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, p):
        while p != self.parent[p]:
            self.parent[p] = self.parent[self.parent[p]]  # 路径压缩
            p = self.parent[p]
        return p

    def union(self, p, q):
        i = self.find(p)
        j = self.find(q)
        if i == j:
            return
        if self.rank[i] > self.rank[j]:
            self.parent[j] = i
        else:
            self.parent[i] = j
            if self.rank[i] == self.rank[j]:
                self.rank[j] += 1


maxn = 10**5 + 1


class Solution:
    fac = [[] for _ in range(maxn)]
    for i in range(2, maxn):
        if len(fac[i]) == 0:
            for j in range(i, maxn, i):
                fac[j].append(i)

    def canTraverseAllPairs(self, nums: List[int]) -> bool:
        if len(nums) == 1:
            return True

        nums = list(set(nums))
        if 1 in nums:
            return False

        n = len(nums)
        uf = UnionFind(n + maxn)

        for i in range(n):
            for p in self.fac[nums[i]]:
                uf.union(i, p + n)

        res = set()
        for i in range(n):
            res.add(uf.find(i))

        return len(res) == 1


def main():
    s = Solution()
    # # Test case 1
    # nums = [28, 39]
    # expected_output = False
    # output = s.canTraverseAllPairs(nums)
    # assert (
    #     output == expected_output
    # ), f"Test case 4 failed: expected {expected_output}, but got {output}"

    # Test case 2
    nums = [21, 88, 75]
    expected_output = False
    output = s.canTraverseAllPairs(nums)
    assert (
        output == expected_output
    ), f"Test case 4 failed: expected {expected_output}, but got {output}"

    print("All test cases passed!")


if __name__ == "__main__":
    main()
