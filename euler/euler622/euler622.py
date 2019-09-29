#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

facs = []


def S(n):
    """
    if 2^i=1mod(n-1):
        S(n)=i

    即 找到 2^i-1 所有因数
    """
    acc = 2
    counter = 1
    while acc % (n-1) != 1:
        acc = acc << 1
        if acc > n:
            acc %= (n-1)
        counter += 1
    return counter


def factorize(n):
    fac = {}
    i = 2
    while i <= n:
        if n % i == 0:
            n //= i
            if fac.get(i):
                fac[i] += 1
            else:
                fac[i] = 1
        else:
            i += 1
    return fac


def dfs(lst, l, acc):
    global facs
    if l == len(lst):
        facs.append(acc)
        return

    for elem in lst[l]:
        dfs(lst, l+1, acc*elem)


def solve(i):
    pass


def main():
    while 1:
        target = int(input())
        lst = []
        mp = factorize(2**target-1)
        print(mp)
        for k, p in mp.items():
            tmp = [1]
            i = 1
            s = k
            while i <= p:
                tmp.append(s)
                i += 1
                s *= k
            lst.append(tmp)

        print(lst)
        dfs(lst, 0, 1)
        global facs
        # print(facs)
        sum = 0
        for elem in facs:
            if elem % 2 == 1 and elem > 2:
                if S(elem+1) == target:
                    sum += (elem+1)
        print(sum)


if __name__ == '__main__':
    main()
