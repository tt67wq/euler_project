#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def PredictTheWinner(self, nums):
        n = len(nums)
        dp = [[[0]*2 for _ in range(n)] for _ in range(n)]
        for i in range(n):
            dp[i][i][0] = nums[i]
        for i in range(n-2, -1, -1):
            for j in range(i+1, n):
                left = dp[i+1][j][1]+nums[i]
                right = dp[i][j-1][1]+nums[j]
                if left > right:
                    dp[i][j][0] = left
                    dp[i][j][1] = dp[i+1][j][0]
                else:
                    dp[i][j][0] = right
                    dp[i][j][1] = dp[i][j-1][0]
        return dp[0][-1][0] >= dp[0][-1][1]


def main():
    pass


if __name__ == '__main__':
    main()
