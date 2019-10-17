#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""
import copy
import random


def xor_test(nums, index):
    nums = list(filter(lambda x: x >= 0, nums))
    s = 0
    for x in nums:
        s ^= x

    if s == 0:
        return True

    win = False
    for i in range(len(nums)):
        origin = nums[i]
        nums[i] = -1
        if xor_test(copy.deepcopy(nums), index+1):
            nums[i] = origin
        else:
            win = True
            break
    return win


def gen_list():
    ls = []
    for i in range(random.randint(1, 10)):
        ls.append(random.randint(0, 10))

    s = 0
    for x in ls:
        s ^= x

    return ls, s


def main():
    while 1:
        input()
        nums, s = gen_list()
        print(len(nums) % 2,  xor_test(nums, 1), bin(s), nums)


if __name__ == '__main__':
    main()
