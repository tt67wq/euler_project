#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""
import copy
import math

MAX = 10**8
cache = {}
ncache = {}


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


def pow(a, b):
    return int(math.pow(a, b))


# r! % n = 0
def naive(n):
    factorial = 1
    result = 0
    while factorial % n != 0:
        result += 1
        factorial *= result
        factorial %= n
    return result


def S(n, ps):
    global cache
    global ncache
    if cache.get(n):
        return n
    best = 0
    for p in ps:
        if p > n:
            break
        if n % p != 0:
            continue

        e = 0
        while n % p == 0:
            n //= p
            e += 1

        if ncache.get(n):
            return max(ncache[n], cache[p][e])
        best = max(best, cache[p][e])
        if n == 1:
            return best
        # if cache.get(n):
        #     return max(best, n)
    return best


def main():
    ps = list(sieve(MAX))

    global cache
    global ncache
    for p in ps:
        cache[p] = {1: p}
        pp = p*p
        e = 2
        while pp <= MAX:
            cache[p][e] = naive(pp)
            pp *= p
            e += 1
    print("cache finished!")

    s = 0
    for i in range(2, MAX+1):
        a = S(i, ps)
        print(i, a)
        ncache[i] = a
        s += a
    print(s)


if __name__ == '__main__':
    main()
