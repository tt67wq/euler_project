#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def sieve(n):
    "Return all primes <= n."
    np1 = n + 1
    s = list(range(np1))
    s[1] = 0
    sqrtn = int(round(n**0.5))
    for i in range(2, sqrtn + 1):
        if s[i]:
            s[i*i: np1: i] = [0] * len(range(i*i, np1, i))
    return filter(None, s)


def sieve_between(a, b):
    "Return all primes in [a, b)."
    ps = sieve(int(round(b**0.5)))
    s = [e+a for e in list(range(b-a))]
    for p in ps:
        op = p
        while p < b:
            if p < a:
                p += op
                continue
            s[p-a] = 0
            p += op

    return filter(None, s)


def main():
    # print(len(list(sieve(1000000))))
    print(list(sieve_between(100, 123)))


if __name__ == '__main__':
    main()
