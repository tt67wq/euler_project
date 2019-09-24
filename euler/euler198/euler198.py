#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def p198(M=10**8, z=100, cnt=0):
    M2 = M/2
    a = m = int(M2**0.5)
    print(a)
    stack = list(range(z, m))
    while stack:
        b = stack[-1]
        if a*b > M2:
            a = stack.pop()
        else:
            cnt += 1
            stack.append(a+b)
    return cnt+M2-z/2


def main():
    print(p198())


if __name__ == '__main__':
    main()
