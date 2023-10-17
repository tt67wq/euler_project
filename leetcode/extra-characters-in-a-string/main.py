#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/extra-characters-in-a-string/

# 给你一个下标从 0 开始的字符串 s 和一个单词字典 dictionary 。你需要将 s 分割成若干个 互不重叠 的子字符串，每个子字符串都在 dictionary 中出现过。s 中可能会有一些 额外的字符 不在任何子字符串中。

# 请你采取最优策略分割 s ，使剩下的字符 最少 。


# 示例 1：

# 输入：s = "leetscode", dictionary = ["leet","code","leetcode"]
# 输出：1
# 解释：将 s 分成两个子字符串：下标从 0 到 3 的 "leet" 和下标从 5 到 8 的 "code" 。只有 1 个字符没有使用（下标为 4），所以我们返回 1 。
# 示例 2：

# 输入：s = "sayhelloworld", dictionary = ["hello","world"]
# 输出：3
# 解释：将 s 分成两个子字符串：下标从 3 到 7 的 "hello" 和下标从 8 到 12 的 "world" 。下标为 0 ，1 和 2 的字符没有使用，所以我们返回 3 。

from typing import List
from functools import cache


class Solution:
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        d = set(dictionary)

        @cache
        def dfs(i: int) -> int:
            if i < 0:
                return 0
            res = dfs(i - 1) + 1  # 不选
            for j in range(i + 1):  # 枚举选哪个
                if s[j : i + 1] in d:
                    res = min(res, dfs(j - 1))
            return res

        return dfs(len(s) - 1)


class TestSolution:
    def test_minExtraChar(self):
        sol = Solution()
        s1 = "leetscode"
        dict1 = ["leet", "code", "leetcode"]
        assert sol.minExtraChar(s1, dict1) == 0

        s2 = "sayhelloworld"
        dict2 = ["hello", "world"]
        assert sol.minExtraChar(s2, dict2) == 3


def main():
    TestSolution().test_minExtraChar()


if __name__ == "__main__":
    main()
