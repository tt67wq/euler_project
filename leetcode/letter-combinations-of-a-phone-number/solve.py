#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

MP = {
    "2": "abc",
    "3": "def",
    "4": "ghi",
    "5": "jkl",
    "6": "mno",
    "7": "pqrs",
    "8": "tuv",
    "9": "wxyz"
}


class Solution:

    def letterCombinations(self, digits):
        if len(digits) == 0:
            return []
        if len(digits) == 1:
            return [x for x in MP[digits]]

        md = len(digits)//2
        res = []
        for x in self.letterCombinations(digits[:md]):
            for y in self.letterCombinations(digits[md:]):
                res.append(x+y)
        return res


def main():
    s = Solution()
    while 1:
        digits = input()
        print(s.letterCombinations(digits))


if __name__ == '__main__':
    main()
