#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def addToArrayForm(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: List[int]
        """
        B = A[::-1]
        l = len(A)
        i = 0
        j = 0
        while j != 0 or i < l or K != 0:
            if i >= l:
                B.append(0)
            B[i] += K % 10
            B[i] += j
            if B[i] > 9:
                B[i] %= 10
                j = 1
            else:
                j = 0
            K //= 10
            i += 1
        return B[::-1]


def main():
    s = Solution()
    print(s.addToArrayForm([2, 1, 5], 806))


if __name__ == '__main__':
    main()
