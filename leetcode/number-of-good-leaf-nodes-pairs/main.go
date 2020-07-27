package main

import "fmt"

// TreeNode is this
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func countPairs(root *TreeNode, distance int) int {
	var ans int = 0
	fmt.Println(dfs(root, distance, &ans))
	return ans
}

func dfs(root *TreeNode, distance int, ans *int) []int {
	if root == nil {
		return []int{}
	}

	if root.Left == nil && root.Right == nil {
		return []int{0}
	}

	var res []int

	left := dfs(root.Left, distance, ans)
	// fmt.Println("left", left)
	for _, e := range left {
		if e+1 > distance {
			continue
		}
		res = append(res, e+1)
	}

	right := dfs(root.Right, distance, ans)
	// fmt.Println("right", right)
	for _, e := range right {
		if e+1 > distance {
			continue
		}
		res = append(res, e+1)
	}

	for _, ld := range left {
		for _, rd := range right {
			if ld+rd+2 <= distance {
				(*ans)++
			}
		}
	}
	return res
}

func main() {
	var n0 TreeNode = TreeNode{1, nil, nil}
	var n1 TreeNode = TreeNode{2, nil, nil}
	var n2 TreeNode = TreeNode{3, nil, nil}
	var n3 TreeNode = TreeNode{4, nil, nil}
	var n4 TreeNode = TreeNode{5, nil, nil}
	var n5 TreeNode = TreeNode{6, nil, nil}
	var n6 TreeNode = TreeNode{7, nil, nil}

	n0.Left = &n1
	n0.Right = &n2
	n1.Left = &n3
	n1.Right = &n4
	n2.Left = &n5
	n2.Right = &n6

	fmt.Println(countPairs(&n0, 3))
}
