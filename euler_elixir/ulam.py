#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "计算乌拉姆序列"

import sys


def U(a, b):
    u = [a, b]
    yield a
    yield b
    even, index = 0, 0

    while even == 0 or u[-1] < 2 * even:
        sums = {}
        for x in range(len(u)):
            for y in range(x + 1, len(u)):
                if sums.get(u[x] + u[y], 0):
                    sums[u[x] + u[y]] += 1
                else:
                    sums[u[x] + u[y]] = 1
        u.append(min(k for k, v in sums.items() if v == 1 and k > u[-1]))
        yield u[-1]
        if u[-1] % 2 == 0:
            even = u[-1]

    while even + u[index] <= u[-1]:
        index += 1  # find first index

    while True:
        if even + u[index] > u[-1] + 2:
            u.append(u[-1] + 2)
        else:
            u.append(even + u[index + 1])
            index += 2
        yield u[-1]


def main():
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    total = int(sys.argv[3])

    u = U(a, b)
    for i in range(total):
        # res.append(str(next(u)))
        print(next(u), end=',')

    # print(",".join(res), end='')


if __name__ == '__main__':
    main()
