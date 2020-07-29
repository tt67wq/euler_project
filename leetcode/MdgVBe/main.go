package main

import "fmt"

// TreeNode is Definition for a binary tree node.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func distanceInTree(root *TreeNode, p int, q int) int {
	pd, dp := dfs(root, p)
	qd, dq := dfs(root, q)

	if pd != qd {
		return dp + dq
	} else if pd == 1 {
		return distanceInTree(root.Left, p, q)
	} else {
		return distanceInTree(root.Right, p, q)
	}
}

func dfs(root *TreeNode, p int) (int, int) {
	if root == nil {
		return 0, -1
	}

	if root.Val == p {
		return 0, 0
	}

	_, ld := dfs(root.Left, p)
	if ld >= 0 {
		return 1, ld + 1
	}
	_, rd := dfs(root.Right, p)
	if rd >= 0 {
		return 2, rd + 1
	}

	return 0, -1
}

func main() {
	n0 := TreeNode{0, nil, nil}
	n1 := TreeNode{3, nil, nil}
	n2 := TreeNode{4, nil, nil}
	n3 := TreeNode{5, nil, nil}
	n4 := TreeNode{1, nil, nil}
	n5 := TreeNode{2, nil, nil}
	n6 := TreeNode{6, nil, nil}

	n0.Left = &n1
	n0.Right = &n2
	n1.Left = &n3
	n1.Right = &n4
	n2.Left = &n5
	n2.Right = &n6

	fmt.Println(distanceInTree(&n0, 2, 6))
}
