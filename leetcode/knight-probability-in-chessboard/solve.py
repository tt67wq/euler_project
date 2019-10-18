#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

CACHE = {}


class Solution:

    def knightProbability(self, N, K, r, c):
        """
        :type N: int
        :type K: int
        :type r: int
        :type c: int
        :rtype: float
        """

        if r >= 0 and r < N and c >= 0 and c < N:
            if K == 0:
                return 1
            else:
                pass
        else:
            return 0

        global CACHE
        fp = "{}:{}:{}:{}".format(N, K, r, c)

        if CACHE.get(fp):
            return CACHE[fp]

        poss = [[r-1, c+2], [r+1, c+2], [r+2, c+1], [r-2, c+1],
                [r-1, c-2], [r+1, c-2], [r+2, c-1], [r-2, c-1]]

        res = 0.0
        for pos in poss:
            res += self.knightProbability(N, K-1, pos[0], pos[1]) * 0.125
        CACHE[fp] = res
        return res


def main():
    s = Solution()

    print(s.knightProbability(10, 13, 5, 3))


if __name__ == '__main__':
    main()
