package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type elem struct {
	tn    *TreeNode
	level int
}

type node struct {
	value interface{}
	next  *node
}

type Queue struct {
	head *node
	tail *node
	size int
}

func (q *Queue) Size() int { return q.size }
func (q *Queue) Pop() interface{} {
	if q.head == nil {
		panic("empty queue")
	}

	var ans *node = q.head

	q.head = q.head.next
	q.size--
	if q.head == nil {
		q.tail = nil
	}

	return ans.value
}
func (q *Queue) Push(value interface{}) {
	var new_node *node = new(node)
	new_node.value = value
	new_node.next = nil

	if q.tail == nil {
		q.head = new_node
		q.tail = new_node
	} else {
		q.tail.next = new_node
		q.tail = new_node
	}
	q.size++
}

func reverse(s []int) []int {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}

/**
 * Definition for a binary tree node.
 */
func levelOrder(root *TreeNode) [][]int {
	var ans [][]int
	var q *Queue
	var e, t *elem
	var es []int
	var i int

	ans = make([][]int, 0)
	q = new(Queue)
	e = new(elem)
	t = new(elem)

	if root == nil {
		return ans
	}

	e.tn = root
	e.level = 0

	q.Push(*e)

	for q.size > 0 {
		*e = q.Pop().(elem)
		if e.level >= len(ans) {
			ans = append(ans, make([]int, 0))
		}
		ans[e.level] = append(ans[e.level], e.tn.Val)

		if e.tn.Left != nil {
			t.tn = e.tn.Left
			t.level = e.level + 1
			q.Push(*t)

		}

		if e.tn.Right != nil {
			t.tn = e.tn.Right
			t.level = e.level + 1
			q.Push(*t)
		}

	}

	for i, es = range ans {
		if i%2 == 1 {
			ans[i] = reverse(es)
		}
	}
	return ans

}

func main() {}
