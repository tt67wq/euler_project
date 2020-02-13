package main

import (
	"fmt"
)

/**
 * Definition for a binary tree node.
 */

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func allPossibleFBT(N int) []*TreeNode {
	if N%2 == 0 {
		return []*TreeNode{}
	}
	var node, t *TreeNode
	var i int
	var ans []*TreeNode

	node = new(TreeNode)
	node.Val = 0
	ans = make([]*TreeNode, 0)

	if N == 1 {
		return []*TreeNode{node}
	}

	for i = 1; i*2+1 <= N; i += 2 {
		for _, x := range allPossibleFBT(i) {
			for _, y := range allPossibleFBT(N - 1 - i) {
				t = new(TreeNode)
				t.Val = 0
				t.Left = x
				t.Right = y
				ans = append(ans, t)

				if i*2 != N-1 {
					t = new(TreeNode)
					t.Val = 0
					t.Left = y
					t.Right = x
					ans = append(ans, t)
				}
			}
		}
	}
	return ans
}

func main() {
	fmt.Println("hehe")
}
