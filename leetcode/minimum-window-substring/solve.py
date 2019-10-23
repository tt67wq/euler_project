#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:

    def minWindow(self, s, t):

        th = {}
        for e in t:
            if th.get(e):
                th[e] += 1
            else:
                th[e] = 1

        ww = len(t)
        flag = 0
        res = ""

        while ww <= len(s):
            if flag == 1:
                break
            index = 0
            flag = 0
            res = ""

            wh = {}
            for e in s[:ww]:
                if wh.get(e):
                    wh[e] += 1
                else:
                    wh[e] = 1

            while index + ww <= len(s):
                d = 0
                for k in th.keys():
                    if wh.get(k) == None:
                        d += th[k]
                    elif wh[k] < th[k]:
                        d += th[k] - wh[k]
                    else:
                        pass

                if d == 0:
                    res = s[index:index + ww]
                    flag = 1
                    break

                if index + ww + d > len(s):
                    break

                for e in s[index:index+d]:
                    wh[e] -= 1

                for e in s[index+ww:index+ww+d]:
                    if wh.get(e):
                        wh[e] += 1
                    else:
                        wh[e] = 1

                index += d
            ww += 1

        return res


def main():
    s = Solution()
    print(s.minWindow("abc", "bc"))


if __name__ == '__main__':
    main()
