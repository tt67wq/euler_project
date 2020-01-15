package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func equal_tree(s *TreeNode, t *TreeNode) bool {
	if s == nil && t == nil {
		return true
	}
	if (s == nil && t != nil) || (s != nil && t == nil) {
		return false
	}
	return s.Val == t.Val && equal_tree(s.Left, t.Left) && equal_tree(s.Right, t.Right)
}

func isSubtree(s *TreeNode, t *TreeNode) bool {
	if equal_tree(s, t) {
		return true
	}
	if s != nil {
		return isSubtree(s.Left, t) || isSubtree(s.Right, t)
	}
	return false
}

func main() {}
