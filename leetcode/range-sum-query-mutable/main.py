#!/usr/bin/env python
# -*- coding: utf-8 -*-

from typing import List


class NumArray:
    """自定义lowbit函数"""

    def lowbit(self, x: int) -> int:
        return x & (-x)

    def __init__(self, nums: List[int]):
        self.tree = [0] + nums  # 构造出的BIT空间比原nums多一，第1个下标0不用
        for i in range(1, len(self.tree)):  # 这种方式构造的BIT时间复杂度为O(n)
            j = i + self.lowbit(i)  # 构造BIT的巧妙方式
            if j < len(self.tree):
                self.tree[j] += self.tree[i]

    def update(self, index: int, val: int) -> None:
        pre_val = self.sumRange(index, index)  # index：在原nums中的位置
        delta = val - pre_val  # 变更值
        i = index + 1  # i: 对应数值在BIT中的位置（index+1）
        while i < len(self.tree):
            self.tree[i] += delta
            i += self.lowbit(i)

    def __preSum(self, index: int) -> int:  # index：在原nums中的位置
        """自定义前缀和preSum函数"""
        i = index + 1  # i: 对应数值在BIT中的位置（index+1）
        summ = 0
        while i:
            summ += self.tree[i]
            i -= self.lowbit(i)
            # i &= i-1        # 跟上一行等价
        return summ

    def sumRange(self, left: int, right: int) -> int:
        return self.__preSum(right) - self.__preSum(left - 1)  # right的前缀和 减去 left-1的前缀和


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# obj.update(index,val)
# param_2 = obj.sumRange(left,right)


def test_NumArray():
    nums = [1, 3, 5, 7, 9]
    num_array = NumArray(nums)
    assert num_array.sumRange(0, 2) == 9
    assert num_array.sumRange(2, 4) == 21
    num_array.update(2, 6)
    assert num_array.sumRange(0, 2) == 10
    assert num_array.sumRange(2, 4) == 22


def main():
    test_NumArray()


if __name__ == "__main__":
    main()
