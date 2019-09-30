#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def p(n):
    """
    after n rounds, the chance for 32 bits to be all 1
    """
    if n == 0:
        return 0

    return (1-0.5**n)**32


def main():

    s = 0.0
    h = {}
    for i in range(1, 500):
        h[i] = p(i)-p(i-1)

    for k, v in h.items():
        s += k*v
    print(s)


if __name__ == '__main__':
    main()
