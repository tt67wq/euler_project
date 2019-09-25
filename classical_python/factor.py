#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def factorize(n):
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
    print(fac)


def main():
    pass


if __name__ == '__main__':
    main()
