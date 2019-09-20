#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def sieve(n):
    "Return all primes <= n."
    np1 = n + 1
    s = list(range(np1))  # leave off `list()` in Python 2
    s[1] = 0
    sqrtn = int(round(n**0.5))
    for i in range(2, sqrtn + 1):  # use `xrange()` in Python 2
        if s[i]:
            # next line:  use `xrange()` in Python 2
            s[i*i: np1: i] = [0] * len(range(i*i, np1, i))
    return filter(None, s)


def main():
    print(len(list(sieve(1000000))))


if __name__ == '__main__':
    main()
