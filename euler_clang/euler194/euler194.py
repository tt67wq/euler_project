#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

from numpy import *


def A(c):
    return (c > 1) * (c-2)*(c**4-7*c**3+20*c**2-29*c+19)


def B(c):
    return (c > 1) * (c**2-2*c+3)*(c-2)**3


def solution(a, b, c):
    A_ = A(c)
    B_ = B(c)
    cc1 = c*(c-1)

    if a == 0:
        return cc1*B_**b
    if b == 0:
        return cc1*A_**a

    # N[a_,b_] == N(a_,b_,c) where a_=1..a, b_=1..b
    N = zeros((a+1, b+1), dtype=object)

    # fill the initial conditions
    N[1:, 0] = cc1*A_**arange(1, a+1, dtype=object)
    N[0, 1:] = cc1*B_**arange(1, b+1, dtype=object)

    # compute other values from the recursion
    for a_ in range(1, a+1):
        for b_ in range(1, b+1):
            N[a_, b_] = N[a_-1, b_]*A_ + N[a_, b_-1]*B_

    return N[a, b] % (10**8)


def main():
    print(solution(25, 75, 1984))


if __name__ == '__main__':
    main()
