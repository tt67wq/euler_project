#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def countArrangement(self, N):
        """
        :type N: int
        :rtype: int
        """
        return self.dp(N, 1, [0]*N, {})

    def dp(self, N, index, vis, cache):

        if index == N + 1:
            return 1

        fp = "{}:{}".format(index, "".join([str(x) for x in vis]))

        if cache.get(fp):
            return cache[fp]

        res = 0
        for e in range(1, N+1):
            if vis[e - 1] == 0 and (e % index == 0 or index % e == 0):
                vis[e - 1] = 1
                res += self.dp(N, index + 1, vis, cache)
                vis[e - 1] = 0

        cache[fp] = res
        return res


def main():
    s = Solution()
    while 1:
        n = int(input())
        print(s.countArrangement(n))


if __name__ == '__main__':
    main()
