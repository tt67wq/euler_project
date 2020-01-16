package main

import (
	"fmt"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// ========== 队列 HEAD ============
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

// ========== 队列 END ============

func average(nums ...int) float64 {
	var s float64

	for _, num := range nums {
		s += float64(num)
	}
	return s / float64(len(nums))
}

func averageOfLevels(root *TreeNode) []float64 {
	if root == nil {
		return []float64{}
	}

	type val struct {
		x     *TreeNode
		level int
	}

	var q *Queue = new(Queue)
	var t0, t1 *val = new(val), new(val)
	var lmp map[int][]int = make(map[int][]int)
	var ans []float64

	t0.x = root
	t0.level = 0

	q.Push(*t0)

	for q.Size() > 0 {
		*t1 = q.Pop().(val)
		if t1.x != nil {
			if _, ok := lmp[t1.level]; ok {
				lmp[t1.level] = append(lmp[t1.level], t1.x.Val)
			} else {
				lmp[t1.level] = []int{t1.x.Val}
			}

			// put left and right to queue
			t0.x = t1.x.Left
			t0.level = t1.level + 1
			q.Push(*t0)

			t0.x = t1.x.Right
			t0.level = t1.level + 1
			q.Push(*t0)
		}
	}

	ans = make([]float64, len(lmp))

	for k, vs := range lmp {
		ans[k] = average(vs...)
	}
	return ans
}

func main() {}
