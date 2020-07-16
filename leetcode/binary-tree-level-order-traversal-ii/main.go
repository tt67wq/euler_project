package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

var MAX int = 1000

func reverse(s [][]int) [][]int {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}

func levelOrderBottom(root *TreeNode) [][]int {
	if root == nil {
		return make([][]int, 0)
	}
	q1 := make([]*TreeNode, MAX)
	q2 := make([]*TreeNode, MAX)
	h1, r1 := 0, 0
	h2 := 0
	ans := make([][]int, 0)

	q1[h1] = root
	h1++

	tmp := make([]int, 0)
	for h1 != r1 {
		x := q1[r1]
		r1++
		tmp = append(tmp, x.Val)

		if x.Left != nil {
			q2[h2] = x.Left
			h2++
		}
		if x.Right != nil {
			q2[h2] = x.Right
			h2++
		}

		if h1 == r1 && h2 != 0 {
			// q1 is empty
			// q2 => q1, q1 = []
			q1 = q2
			h1 = h2
			r1 = 0

			q2 = make([]*TreeNode, MAX)
			h2 = 0
			ans = append(ans, tmp)
			tmp = []int{}
		}
	}
	ans = append(ans, tmp)
	return reverse(ans)
}

func main() {
	n0 := TreeNode{3, nil, nil}
	n1 := TreeNode{9, nil, nil}
	n2 := TreeNode{20, nil, nil}
	n3 := TreeNode{15, nil, nil}
	n4 := TreeNode{7, nil, nil}

	n0.Left = &n1
	n0.Right = &n2
	n2.Left = &n3
	n2.Right = &n4

	fmt.Println(levelOrderBottom(&n0))

}
