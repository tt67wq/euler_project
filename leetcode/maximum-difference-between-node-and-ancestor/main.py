#!/usr/bin/env python
# -*- coding: utf-8 -*-

from token import OP
from typing import Optional

# 给定二叉树的根节点 root，找出存在于 不同 节点 A 和 B 之间的最大值 V，其中 V = |A.val - B.val|，且 A 是 B 的祖先。

# （如果 A 的任何子节点之一为 B，或者 A 的任何子节点是 B 的祖先，那么我们认为 A 是 B 的祖先）

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        return self.dfs(root, root.val, root.val)

    def dfs(self, root: Optional[TreeNode], mi: int, ma: int) -> int:
        if root is None:
            return 0
        diff = max(abs(root.val - mi), abs(root.val - ma))
        mi, ma = min(mi, root.val), max(ma, root.val)
        diff = max(diff, self.dfs(root.left, mi, ma))
        diff = max(diff, self.dfs(root.right, mi, ma))
        return diff


def main():
    pass


if __name__ == "__main__":
    main()
