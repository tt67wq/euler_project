#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""
import copy
import math

MAX = 100
cache = {}


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


def factorial(n):
    s = 1
    while n > 1:
        s *= n
        n -= 1
    return s


def pow(a, b):
    return int(math.pow(a, b))


# cache s(p^a) = p*i
def cache_for(p, a):
    global cache

    n = pow(p, a)
    if n > MAX:
        return 0
    i = 2
    while 1:
        if factorial(p*i) % n == 0:
            break
        else:
            i += 1
    if cache.get(p):
        cache[p][a] = p*i
    else:
        cache[p] = {a: p*i}
    return 1


def cache_all(ps):
    for p in ps:
        a = 3
        while 1:
            if cache_for(p, a):
                a += 1
            else:
                break


def S(n):
    fac = {}
    i = 2
    while i <= n:
        if n % i == 0:
            n /= i
            if fac.get(i):
                fac[i] += 1
            else:
                fac[i] = 1
        else:
            i += 1

    vs = []
    global cache
    for k, v in fac.items():
        if v == 1:
            vs.append(k)
        elif v == 2:
            vs.append(k*2)
        else:
            vs.append(cache[k][v])
    return max(vs)


def main():
    ps = list(sieve(MAX))
    cache_all(ps)
    # global cache
    # print(cache)
    s = 0
    for i in range(2, MAX+1):
        s += S(i)
        print(i, S(i))
    print(s)


if __name__ == '__main__':
    main()
