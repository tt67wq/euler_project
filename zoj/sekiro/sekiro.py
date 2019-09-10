#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

import math


def solve(money, death):
    while death > 0 and money > 1:
        money /= 2
        money = math.ceil(money)
        death -= 1
    return money



def main():
    cs = int(input())
    while cs > 0:
        tmp = [int(i) for i in input().split(' ')]
        print(solve(tmp[0], tmp[1]))
        cs -= 1


if __name__ == '__main__':
    main()
