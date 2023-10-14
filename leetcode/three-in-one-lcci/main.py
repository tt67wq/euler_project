#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/three-in-one-lcci/

import unittest


class TripleInOne:
    def __init__(self, stackSize: int):
        """
        :type stackSize: int
        """
        self.stack_size = stackSize
        self.stack = [-1] * (stackSize + 1) * 3

    def push(self, stackNum: int, value: int) -> None:
        """
        :type stackNum: int
        :type value: int
        :rtype: None
        """
        stack_top_idx = (stackNum - 1) * (self.stack_size + 1)
        stack_top = self.stack[stack_top_idx]
        if stack_top + 1 == self.stack_size:
            return
        self.stack[stack_top_idx] += 1
        self.stack[stack_top_idx + self.stack[stack_top_idx] + 1] = value

    def pop(self, stackNum: int) -> int:
        """
        :type stackNum: int
        :rtype: int
        """
        stack_top_idx = (stackNum - 1) * (self.stack_size + 1)
        stack_top = self.stack[stack_top_idx]
        if stack_top == -1:
            return -1

        to_pop = self.stack[stack_top_idx + stack_top + 1]
        self.stack[stack_top_idx] -= 1

        return to_pop

    def peek(self, stackNum: int) -> int:
        """
        :type stackNum: int
        :rtype: int
        """
        stack_top_idx = (stackNum - 1) * (self.stack_size + 1)
        stack_top = self.stack[stack_top_idx]
        if stack_top == -1:
            return -1
        return self.stack[stack_top_idx + stack_top + 1]

    def isEmpty(self, stackNum: int) -> bool:
        """
        :type stackNum: int
        :rtype: bool
        """
        stack_top_idx = (stackNum - 1) * (self.stack_size + 1)
        stack_top = self.stack[stack_top_idx]
        return stack_top == -1


# Your TripleInOne object will be instantiated and called as such:
# obj = TripleInOne(stackSize)
# obj.push(stackNum,value)
# param_2 = obj.pop(stackNum)
# param_3 = obj.peek(stackNum)
# param_4 = obj.isEmpty(stackNum)


class TestTripleInOne(unittest.TestCase):
    def test_push_pop(self):
        stack = TripleInOne(3)
        stack.push(1, 1)
        stack.push(1, 2)
        stack.push(1, 3)
        self.assertEqual(stack.pop(1), 3)
        self.assertEqual(stack.pop(1), 2)
        self.assertEqual(stack.pop(1), 1)
        self.assertEqual(stack.pop(1), -1)

    def test_peek(self):
        stack = TripleInOne(3)
        stack.push(2, 1)
        stack.push(2, 2)
        stack.push(2, 3)
        self.assertEqual(stack.peek(2), 3)
        self.assertEqual(stack.pop(2), 3)
        self.assertEqual(stack.peek(2), 2)
        self.assertEqual(stack.pop(2), 2)
        self.assertEqual(stack.peek(2), 1)
        self.assertEqual(stack.pop(2), 1)
        self.assertEqual(stack.peek(2), -1)

    def test_isEmpty(self):
        stack = TripleInOne(3)
        self.assertTrue(stack.isEmpty(1))
        self.assertTrue(stack.isEmpty(2))
        self.assertTrue(stack.isEmpty(3))
        stack.push(1, 1)
        self.assertFalse(stack.isEmpty(1))
        self.assertTrue(stack.isEmpty(2))
        self.assertTrue(stack.isEmpty(3))
        stack.pop(1)
        self.assertTrue(stack.isEmpty(1))
        self.assertTrue(stack.isEmpty(2))
        self.assertTrue(stack.isEmpty(3))


def main():
    unittest.main()


if __name__ == "__main__":
    main()
