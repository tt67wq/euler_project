#!/usr/bin/env python
# -*- coding: utf-8 -*-

# 给定一个布尔表达式和一个期望的布尔结果 result，
# 布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR) 和 ^ (XOR) 符号组成。
# 实现一个函数，算出有几种可使该表达式得出 result 值的括号方法。

# 示例 1:

# 输入: s = "1^0|0|1", result = 0

# 输出: 2
# 解释: 两种可能的括号方法是
# 1^(0|(0|1))
# 1^((0|0)|1)
# 示例 2:

# 输入: s = "0&0&0&1^1|0", result = 1

# 输出: 10
# 提示：

# 运算符的数量不超过 19 个


from typing import Dict


class Solution:
    def countEval(self, s: str, result: int) -> int:
        self.ops = {
            "&": {
                True: [(True, True)],
                False: [(True, False), (False, True), (False, False)],
            },
            "|": {
                True: [(True, False), (False, True), (True, True)],
                False: [(False, False)],
            },
            "^": {
                True: [(True, False), (False, True)],
                False: [(True, True), (False, False)],
            },
        }
        return self.__dfs(s, result, {})

    def __dfs(self, expression: str, result: int, memo: Dict) -> int:
        # 查询备忘录，有结果则直接返回
        if (expression, result) in memo:
            return memo[(expression, result)]

        # 边界情况
        if len(expression) == 1:
            val = int(expression)
            return int(val == result)

        # 递归计算左右子式的结果
        total = 0
        for i in range(len(expression)):
            char = expression[i]
            if char in self.ops:
                for lr, rr in self.ops[char][bool(result)]:
                    left = expression[:i]
                    right = expression[i + 1 :]
                    total += self.__dfs(left, lr, memo) * self.__dfs(right, rr, memo)
        memo[(expression, result)] = total
        return total


def test_countEval():
    s = Solution()
    assert s.countEval("1", 1) == 1
    assert s.countEval("0", 0) == 1
    assert s.countEval("1|0", 0) == 0
    assert s.countEval("1^0", 1) == 1
    assert s.countEval("1&0", 1) == 0
    assert s.countEval("1|0&1", 1) == 2
    assert s.countEval("1^0|0|1", 0) == 2
    # assert s.countEval("1&0|0|1^1&0&1|1", 0) == 6


def main():
    test_countEval()


if __name__ == "__main__":
    main()
