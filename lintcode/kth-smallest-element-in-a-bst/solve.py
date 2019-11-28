#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""

"""
Definition of TreeNode:
"""


class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None


class Solution:

    """
    @param root: the given BST
    @param k: the given k
    @return: the kth smallest element in BST
    """

    def kthSmallest(self, root, k):
        # write your code here
        acc = []
        self.dfs(root, acc)
        return acc[k-1]

    def dfs(self, root, acc):
        if root == None:
            return

        self.dfs(root.left, acc)
        acc.append(root.val)
        self.dfs(root.right, acc)


def main():
    pass


if __name__ == '__main__':
    main()
