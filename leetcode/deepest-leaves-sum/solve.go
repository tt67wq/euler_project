package main

import (
// "fmt"
)

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

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

type Elem struct {
	Tn    *TreeNode
	Level int
}

func deepestLeavesSum(root *TreeNode) int {
	if root == nil {
		return 0
	}
	var q *Queue
	var t0, t1 *Elem
	var m int
	var vis map[int]int

	q = new(Queue)
	t0 = new(Elem)
	t1 = new(Elem)
	vis = make(map[int]int)
	m = 0

	t0.Tn = root
	t0.Level = 0
	q.Push(*t0)

	for q.size > 0 {
		*t0 = q.Pop().(Elem)
		vis[t0.Level] += t0.Tn.Val
		if t0.Level > m {
			m = t0.Level
		}
		if t0.Tn.Left != nil {
			t1.Tn = t0.Tn.Left
			t1.Level = t0.Level + 1
			q.Push(*t1)
		}

		if t0.Tn.Right != nil {
			t1.Tn = t0.Tn.Right
			t1.Level = t0.Level + 1
			q.Push(*t1)
		}
	}
	return vis[m]

}

func main() {}
