#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/


class Solution:
    def getHappyString(self, n: int, k: int) -> str:
        base = 2 ** (n - 1)
        res = ""

        if k > base * 3:
            return ""

        # 首字母 三种情况
        level = ((k - 1) // base) if k else 0
        res += "abc"[level]
        base *= level

        # 其余字母 两种情况
        for i in range(2, n + 1):
            temp = 2 ** (n - i)
            if k > base + temp:
                base += temp
                res += "b" if res[-1] == "c" else "c"
            else:
                res += "b" if res[-1] == "a" else "a"

        return res


def test_getHappyString():
    s = Solution()
    assert s.getHappyString(1, 3) == "c"
    assert s.getHappyString(3, 9) == "cab"
    assert s.getHappyString(2, 7) == ""
    assert s.getHappyString(10, 100) == "abacbabacb"


def main():
    test_getHappyString()


if __name__ == "__main__":
    main()
