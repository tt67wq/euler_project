#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:

    def max_range(self, n):
        return "".join(sorted(n)[::-1])

    def nextGreaterElement(self, n):
        if n < 10:
            return -1

        head = [str(n)[0]]
        tail = str(n)[1:]
        while tail != self.max_range(tail):
            head.append(tail[0])
            tail = tail[1:]

        tail = list(tail)
        m = head[-1]
        ts = []
        for x in tail:
            if x > m:
                ts.append(x)

        if len(ts) == 0:
            return -1

        head[-1] = min(ts)

        for i in range(len(tail)):
            if tail[i] == head[-1]:
                tail[i] = m
                break

        res = int("".join(head+sorted(tail)))
        if res > 2**31:
            return -1
        return res


def main():
    s = Solution()
    while 1:
        n = int(input())
        print(s.nextGreaterElement(n))


if __name__ == '__main__':
    main()
