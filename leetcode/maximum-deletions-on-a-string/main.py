#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/maximum-deletions-on-a-string/


class Solution:
    """
    f(i) => 删除后缀s[i:]所需要的最大删除次数

    if s[i:i+j] == s[i+j:i+2j] do
        f(i) = f(i+j) + 1
    else
        f(i) = 1
    end

    ans = f(0)
    """

    def deleteString(self, s: str) -> int:
        n = len(s)
        if len(set(s)) == 1:
            return n  # 全部相同，直接删除到空串

        # lcp[i][j] 表示 s[i:] 和 s[j:] 的最长公共前缀
        lcp = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, i, -1):
                if s[i] == s[j]:
                    lcp[i][j] = lcp[i + 1][j + 1] + 1

        # f(i) => 删除后缀s[i:]所需要的最大删除次数
        f = [0] * n
        for i in range(n - 1, -1, -1):
            for j in range(1, (n - i) // 2 + 1):
                # s[i:]和s[i+j:]的最长公共前缀长度大于等于j => s[i:i+j] == s[i+j:i+2j]
                if lcp[i][i + j] >= j:
                    f[i] = max(f[i], f[i + j])
            f[i] += 1
        return f[0]


def main():
    pass


if __name__ == "__main__":
    main()
