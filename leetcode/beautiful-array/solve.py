#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

CACHE = {}


class Solution(object):
    def beautifulArray(self, N):
        """
        :type N: int
        :rtype: List[int]
        """
        global CACHE
        if N == 1:
            return [1]

        if N == 2:
            return [1, 2]

        if CACHE.get(N):
            return CACHE[N]

        if N % 2 == 1:
            # odd
            odds = self.beautifulArray((N+1)//2)
            # even
            evens = self.beautifulArray(N//2)
            res = [2*x-1 for x in odds] + [2*x for x in evens if 2*x < N]
        else:
            bs = self.beautifulArray(N//2)
            res = [2*x-1 for x in bs] + [N] + [2*x for x in bs if 2*x < N]

        CACHE[N] = res
        return res


def main():
    s = Solution()
    while 1:
        n = int(input())
        print(s.beautifulArray(n))


if __name__ == '__main__':
    main()
