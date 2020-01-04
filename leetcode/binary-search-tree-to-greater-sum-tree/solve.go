package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func bstToGst(root *TreeNode) *TreeNode {
	bst_with(root, 0)
	return root
}

func sum_of_tree(root *TreeNode) int {
	if root == nil {
		return 0
	}
	var ans int = 0

	ans += root.Val
	if root.Left != nil {
		ans += sum_of_tree(root.Left)
	}

	if root.Right != nil {
		ans += sum_of_tree(root.Right)
	}
	return ans
}

func bst_with(root *TreeNode, n int) {
	if root == nil {
		return
	}
	root.Val += n
	root.Val += sum_of_tree(root.Right)

	if root.Right != nil {
		bst_with(root.Right, n)
	}
	if root.Left != nil {
		bst_with(root.Left, root.Val)
	}
}

func main() {}
