#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

MAX = 10**7
PS = []


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


def largest_prime(n):
    fac = {}
    i = 0
    global PS
    while PS[i] <= n:
        if n % PS[i] == 0:
            n //= PS[i]
            if fac.get(PS[i]):
                fac[PS[i]] *= PS[i]
            else:
                fac[PS[i]] = PS[i]
        else:
            i += 1
    return max(list(fac.values()))


def M(n):
    for i in range(n-1, 0, -1):
        if (i**2) % n == i:
            return i


def main():
    global PS
    PS = list(sieve(MAX))


if __name__ == '__main__':
    main()
