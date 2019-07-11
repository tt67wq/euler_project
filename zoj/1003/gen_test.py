#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

import random


def gen_pair():
    return [random.randint(10000, 1000000), random.randint(1, 100000)]


def main():
    with open("test.txt", "wb") as f:
        for i in range(20):
            pair = gen_pair()
            content = "{} {}\n".format(pair[0], pair[1])
            f.write(content.encode("utf8"))


if __name__ == '__main__':
    main()
