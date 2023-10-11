#!/usr/bin/env python
# -*- coding: utf-8 -*-
from optparse import Option
from typing import Optional

import unittest


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        if root.left is None and root.right is None:
            return root.val
        return max(self.dfs(root))

    # dfs -> (rob_root, not_rob_root)
    def dfs(self, root: Optional[TreeNode]) -> (int, int):
        if root is None:
            return 0, 0

        lr, lrn = self.dfs(root.left)
        rr, rrn = self.dfs(root.right)
        return root.val + lrn + rrn, max(lr, lrn) + max(rr, rrn)


class TestSolution(unittest.TestCase):
    def test_rob(self):
        # Test case 1
        root = TreeNode(3)
        root.left = TreeNode(2)
        root.right = TreeNode(3)
        root.left.right = TreeNode(3)
        root.right.right = TreeNode(1)
        self.assertEqual(Solution().rob(root), 7)

        # Test case 2
        root = TreeNode(3)
        root.left = TreeNode(4)
        root.right = TreeNode(5)
        root.left.left = TreeNode(1)
        root.left.right = TreeNode(3)
        root.right.right = TreeNode(1)
        self.assertEqual(Solution().rob(root), 9)


def main():
    unittest.main()


if __name__ == "__main__":
    main()
