#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

import sys


def manacher(cs):
    s = '#' + '#'.join(cs) + '#'
    lens = len(s)
    p = [0] * lens
    mx = 0
    id = 0
    for i in range(lens):
        if mx > i:
            p[i] = min(mx-i, p[int(2*id-i)])
        else:
            p[i] = 1
        while i-p[i] >= 0 and i+p[i] < lens and s[i-p[i]] == s[i+p[i]]:
            p[i] += 1
        if(i+p[i]) > mx:
            mx, id = i+p[i], i

    counter = 0
    for i in range(len(p)):
        if(p[i]-1 > 1):
            # ps = s[i-(p[i]-1):i+p[i]]
            # print(ps.replace('#', ''), p[i]-1)
            counter += 1
    return counter


def solve(s, t):
    if s == t:
        return manacher(s) + len(s)

    start = 0
    end = 0
    l = len(s)
    count = 0

    for i in range(l):
        if s[i] == t[i]:
            continue
        else:
            start = i
            break

    for i in range(l-1, 0, -1):
        if s[i] == t[i]:
            continue
        else:
            end = i
            break
    if s[start:end+1] == t[end:start-1:-1]:
        count += 1
    else:
        return 0

    start -= 1
    end += 1

    while 1:
        if(s[start] != s[end]):
            break
        start -= 1
        end += 1
        count += 1

    return count


def main():
    tc = int(input())

    while tc > 0:
        s = input()
        t = input()
        print(solve(s, t))
        tc -= 1

    sys.exit()


if __name__ == '__main__':
    main()
