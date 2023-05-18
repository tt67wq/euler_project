#!/usr/bin/env python
# -*- coding: utf-8 -*-


class Solution:
    """
    给定正整数 n ，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。

    如果我们可以通过上述方式得到 2 的幂，返回 true；否则，返回 false。



    示例 1：

    输入：n = 1
    输出：true
    示例 2：

    输入：n = 10
    输出：false


    提示：

    1 <= n <= 109
    """

    def isPowerOf2(self, n: int) -> bool:
        if n <= 0:
            return False
        return n & (n - 1) == 0

    def reorderedPowerOf2(self, n: int) -> bool:
        nums = sorted(list(str(n)))
        m = len(nums)
        vis = [False] * m

        def backtrack(i: int, num: int) -> bool:
            if i == m:
                return self.isPowerOf2(num)
            for j, ch in enumerate(nums):
                if (
                    (num == 0 and ch == "0")
                    or vis[j]
                    or (j > 0 and nums[j] == nums[j - 1] and not vis[j - 1])
                ):
                    continue
                vis[j] = True
                if backtrack(i + 1, num * 10 + ord(ch) - ord("0")):
                    return True
                vis[j] = False
            return False

        return backtrack(0, 0)


def main():
    pass


if __name__ == "__main__":
    main()
