#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def incr(self, mp, k):
        if mp.get(k):
            mp[k] += 1
        else:
            mp[k] = 1

    def fourSumCount(self, A, B, C, D):
        ps = {}
        ns = {}
        zs = 0
        for x in A:
            for y in B:
                if x+y > 0:
                    self.incr(ps, x+y)
                elif x+y < 0:
                    self.incr(ns, x+y)
                else:
                    zs += 1

        ps2 = {}
        ns2 = {}
        zs2 = 0
        for x in C:
            for y in D:
                if x+y > 0:
                    self.incr(ps2, x+y)
                elif x+y < 0:
                    self.incr(ns2, x+y)
                else:
                    zs2 += 1

        # print(ps, ns, ps2, ns2, zs, zs2)
        res = zs*zs2

        k1 = sorted(list(ps.keys()))
        k2 = sorted(list(ns2.keys()))

        i, j = 0, len(k2)-1

        while i < len(k1) and j >= 0:
            t = k1[i]+k2[j]
            if t < 0:
                i += 1
            elif t > 0:
                j -= 1
            else:
                res += ps[k1[i]]*ns2[k2[j]]
                i += 1
                j -= 1

        k1 = sorted(list(ps2.keys()))
        k2 = sorted(list(ns.keys()))

        i, j = 0, len(k2)-1

        while i < len(k1) and j >= 0:
            t = k1[i]+k2[j]
            if t < 0:
                i += 1
            elif t > 0:
                j -= 1
            else:
                res += ps2[k1[i]]*ns[k2[j]]
                i += 1
                j -= 1

        return res


def main():
    pass


if __name__ == '__main__':
    main()
