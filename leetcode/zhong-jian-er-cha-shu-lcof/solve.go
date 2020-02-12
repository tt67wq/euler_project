package main

import (
	"fmt"
)

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func buildTree(preorder []int, inorder []int) *TreeNode {
	if len(preorder) == 0 {
		return nil
	}
	var h, idx int
	var ans *TreeNode

	ans = new(TreeNode)
	h = preorder[0]
	idx = find_index(inorder, h)
	ans.Val = h
	ans.Left = buildTree(preorder[1:1+idx], inorder[:idx])
	ans.Right = buildTree(preorder[idx+1:], inorder[idx+1:])
	return ans
}

func find_index(ns []int, t int) int {
	for i, n := range ns {
		if n == t {
			return i
		}
	}
	return -1
}

func main() {}
