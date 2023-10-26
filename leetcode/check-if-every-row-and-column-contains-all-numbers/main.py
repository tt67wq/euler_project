#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/check-if-every-row-and-column-contains-all-numbers/description/

from typing import List


class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        l = len(matrix)

        # check row
        for i in range(l):
            if len(set(matrix[i])) != l:
                return False

        # check column
        for i in range(l):
            col = []
            for j in range(l):
                col.append(matrix[j][i])
            if len(set(col)) != l:
                return False

        return True


def main():
    pass


if __name__ == "__main__":
    main()
