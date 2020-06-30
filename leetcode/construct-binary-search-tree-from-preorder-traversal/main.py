#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> TreeNode:
        if len(preorder) == 0:
            return None
            
        ans = TreeNode()
        ans.val = preorder[0]
        preorder_left = [x for x in preorder if x < ans.val]
        preorder_right = [x for x in preorder if x > ans.val]
        ans.left = self.bstFromPreorder(preorder_left)
        ans.right = self.bstFromPreorder(preorder_right)
        return ans


def main():
    pass


if __name__ == "__main__":
    main()
