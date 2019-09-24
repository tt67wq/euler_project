#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

top = 10000000


def divisors():
    divs = [0]*top
    for i in range(2, top):
        for j in range(1, min(i, top//i)+1):
            k = i*j
            if k > top-1:
                continue
            if i == j:
                divs[k] += 1
            else:
                divs[k] += 2

    return divs


def main():
    counter = 0
    divs = divisors()
    for i in range(1, top-1):
        if divs[i] > 0 and divs[i] == divs[i+1]:
            print(i, i+1, divs[i])
            counter += 1
    print("total nums", counter)


if __name__ == '__main__':
    main()
