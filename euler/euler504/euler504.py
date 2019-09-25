#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

# s = i + b/2 - 1
# i = s + 1 - b/2
import math


def is_sqr(n):
    a = int(math.sqrt(n))
    return a * a == n


def gcd(a, b):
    while a % b:
        a, b = b, a % b
    return b


def main():
    m = int(input())
    count = 0
    cache = {}

    for a in range(1, m+1):
        for b in range(1, m+1):
            for c in range(1, m+1):
                for d in range(1, m+1):
                    ds = gcd(a, b)+gcd(b, c)+gcd(c, d)+gcd(d, a)
                    s = (a*b+b*c+c*d+d*a)//2
                    inner = s+1-ds//2
                    if inner > 0 and is_sqr(inner):
                        # print(a, b, c, d, inner)
                        # count += all_range([a, b, c, d])
                        count += 1
    print(count)


if __name__ == '__main__':
    main()
