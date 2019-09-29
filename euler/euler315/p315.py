#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""
LIGHTS_MAP = {0: 119, 1: 36, 2: 93, 3: 109, 4: 46, 5: 107, 6: 123, 7: 39, 8: 127, 9: 111}
trans_map = {}


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


def trans():
    global trans_map
    for i in range(10):
        trans_map[i] = {}
        for j in range(10):
            bm = bin(LIGHTS_MAP[i] & LIGHTS_MAP[j])
            counter = 0
            for letter in bm[2:]:
                if letter == '1':
                    counter += 1
            trans_map[i][j] = counter


def digital_root_chain(n):
    chain = [n]
    while n > 9:
        m = n
        s = 0
        while m > 0:
            s += m % 10
            m //= 10
        n = s
        chain.append(n)
    return chain


def diff(a, b):
    s = 0
    global trans_map
    while a > 0 and b > 0:
        s += trans_map[a % 10][b % 10]
        a //= 10
        b //= 10
    return s


def main():
    trans()
    # print(trans_map)
    s = 0
    for p in sieve_between(10**7, 2*10**7):
        chain = digital_root_chain(p)
        ts = 0
        for i in range(len(chain)-1):
            ts += diff(chain[i], chain[i+1])

        s += ts
    print(s * 2)


if __name__ == '__main__':
    main()
