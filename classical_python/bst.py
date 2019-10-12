#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self, root=None):
        self.root = root

    # Find the node with the minimum value
    def find_min(self, node):
        if node is None:
            return None
        current = node
        while current.left is not None:
            current = current.left
        return current

    # Find the node with the maximum value
    def find_max(self):
        if self.root is None:
            return None
        current = self.root
        while current.right is not None:
            current = current.right
        return current

    # Insert a node with data into the BST
    def insert(self, data):
        node = TreeNode(data)
        if self.root is None:
            self.root = node
        else:
            current = self.root
            while True:
                if data < current.val:
                    if current.left is None:
                        current.left = node
                        return
                    current = current.left
                else:
                    if current.right is None:
                        current.right = node
                        return
                    current = current.right

    def delete(self, data):
        return self.delNode(self.root, data)

    def delNode(self, root, val):
        if root == None:
            return
        if val < root.val:
            root.left = self.delNode(root.left, val)
        elif val > root.val:
            root.right = self.delNode(root.right, val)
        # 当val == root.val时，分为三种情况：只有左子树或者只有右子树、有左右子树、即无左子树又无右子树
        else:
            if root.left and root.right:
                # 既有左子树又有右子树，则需找到右子树中最小值节点
                temp = self.find_min(root.right)
                root.val = temp.val
                # 再把右子树中最小值节点删除
                root.right = self.delNode(root.right, temp.val)
            elif root.right == None and root.left == None:
                # 左右子树都为空
                root = None
            elif root.right == None:
                # 只有左子树
                root = root.left
            elif root.left == None:
                # 只有右子树
                root = root.right
        return root

    # Search for the node with data

    def search(self, data):
        current = self.root
        while current is not None:
            if current.val == data:
                return current
            current = current.left if data < current.val else current.right
        return current


def main():
    pass


if __name__ == '__main__':
    main()
