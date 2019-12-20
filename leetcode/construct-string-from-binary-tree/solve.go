package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func tree2str(t *TreeNode) string {
	if t == nil {
		return ""
	}

	var left, right string

	left = tree2str(t.Left)
	right = tree2str(t.Right)

	if left == "" && right == "" {
		return fmt.Sprintf("%d", t.Val)
	} else if left == "" && right != "" {
		return fmt.Sprintf("%d()(%s)", t.Val, right)
	} else if left != "" && right == "" {
		return fmt.Sprintf("%d(%s)", t.Val, left)
	} else {
		return fmt.Sprintf("%d(%s)(%s)", t.Val, left, right)
	}

	return ""
}

func main() {}
