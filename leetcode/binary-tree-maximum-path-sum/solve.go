package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func maxPathSum(root *TreeNode) int {
	if root == nil {
		return 0
	}

	var ans int

	ans = MinInt

	find_max(root, &ans)
	return ans
}

func find_max(root *TreeNode, ans *int) int {
	if root == nil {
		return 0
	}

	var left, right int

	left = max(0, find_max(root.Left, ans))
	right = max(0, find_max(root.Right, ans))

	*ans = max(*ans, root.Val+left+right)
	return max(left, right) + root.Val

}

func max(nums ...int) int {
	var m int

	m = 0
	for _, num := range nums {
		if num > m {
			m = num
		}
	}
	return m
}

func main() {}
