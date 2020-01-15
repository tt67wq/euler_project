package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func abs(n int) int {
	if n < 0 {
		return -n
	}
	return n
}

func sumOfTree(root *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	var s int
	var st0, st1, st2 *TreeNode

	s = root.Val

	st1 = sumOfTree(root.Left)
	st2 = sumOfTree(root.Right)

	if st1 != nil {
		s += st1.Val
	}
	if st2 != nil {
		s += st2.Val
	}

	st0 = new(TreeNode)
	st0.Val = s
	st0.Left = st1
	st0.Right = st2

	return st0
}

func podu(root *TreeNode) int {
	if root == nil {
		return 0
	}
	if root.Left == nil && root.Right == nil {
		return 0
	}
	if root.Left == nil && root.Right != nil {
		return root.Right.Val
	}
	if root.Left != nil && root.Right == nil {
		return root.Left.Val
	}

	return abs(root.Left.Val - root.Right.Val)
}

func doFindTilt(root *TreeNode) int {
	if root == nil {
		return 0
	}

	return podu(root) + doFindTilt(root.Left) + doFindTilt(root.Right)
}

func findTilt(root *TreeNode) int {
	if root == nil {
		return 0
	}
	var sroot *TreeNode

	sroot = sumOfTree(root)
	return doFindTilt(sroot)
}

func main() {}
