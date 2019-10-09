#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

from functools import reduce

MAX = 10**7
PS = []
PSET = set()


def egcd(a, b):
    """扩展欧几里得"""
    if 0 == b:
        return 1, 0, a
    x, y, q = egcd(b, a % b)
    x, y = y, (x - a // b * y)
    return x, y, q


def chinese_remainder(pairs):
    """中国剩余定理"""
    mod_list, remainder_list = [p[0] for p in pairs], [p[1] for p in pairs]
    mod_product = reduce(lambda x, y: x * y, mod_list)
    mi_list = [mod_product//x for x in mod_list]
    mi_inverse = [egcd(mi_list[i], mod_list[i])[0] for i in range(len(mi_list))]
    x = 0
    for i in range(len(remainder_list)):
        x += mi_list[i] * mi_inverse[i] * remainder_list[i]
        x %= mod_product
    return x


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


def factorize(n):
    global PS
    fac = {}
    i = 0
    while PS[i] <= n:
        if n % PS[i] == 0:
            n //= PS[i]
            if fac.get(PS[i]):
                fac[PS[i]] *= PS[i]
            else:
                fac[PS[i]] = PS[i]
        else:
            i += 1
    return list(fac.values())


def test_M(n):
    for i in range(n-1, 0, -1):
        if (i**2) % n == i:
            return i


def bin_combine(n):
    cmb = []
    for i in range(1, 2**n-1):
        tmp = bin(i)[2:]
        cmb.append([0]*(n-len(tmp))+[int(x) for x in tmp])
    return cmb


def M(n):
    facs = factorize(n)
    if len(facs) == 1:
        return 1
    m = 0
    for x in bin_combine(len(facs)):
        tmp = chinese_remainder(list(zip(facs, x)))
        if tmp > m:
            m = tmp
    return m


def main():
    global PS
    PS = list(sieve(MAX))

    s = 0
    for i in range(2, MAX+1):
        tmp = M(i)
        print(i, tmp)
        s += tmp
    print(s)


if __name__ == '__main__':
    main()
