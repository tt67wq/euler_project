#!/usr/bin/env python
# -*- coding: utf-8 -*-

# 给你一个整数 n，请你每隔三位添加点（即 "." 符号）作为千位分隔符，并将结果以字符串格式返回。


# 示例 1：

# 输入：n = 987
# 输出："987"
# 示例 2：

# 输入：n = 1234
# 输出："1.234"
# 示例 3：

# 输入：n = 123456789
# 输出："123.456.789"
# 示例 4：

# 输入：n = 0
# 输出："0"


class Solution:
    def thousandSeparator(self, n: int) -> str:
        ns = []
        while n >= 1000:
            ns.append(str(n % 1000).zfill(3))
            n //= 1000

        ns.append(str(n))
        return ".".join(ns[::-1])


def main():
    s = Solution()
    print(s.thousandSeparator(123456789))
    print(s.thousandSeparator(1234))
    print(s.thousandSeparator(987))
    print(s.thousandSeparator(1000))
    print(s.thousandSeparator(0))


if __name__ == "__main__":
    main()
