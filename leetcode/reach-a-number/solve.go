package main

import (
	"fmt"
)

type val struct {
	x int
	y int
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

func reachNumber(target int) int {
	if target == 0 {
		return 0
	}
	var ans int
	var vis map[int]int
	var q *Queue
	var t, t0 *val

	vis = make(map[int]int)
	q = new(Queue)
	t = new(val)
	t0 = new(val)

	t.x = 0
	t.y = 0

	q.Push(*t)
	vis[0] = 0

	for {
		*t = q.Pop().(val)

		t0.x = t.x + t.y + 1
		t0.y = t.y + 1
		if t0.x == target {
			ans = t0.y
			break
		}
		if vis[t0.x] == 0 {
			vis[t0.x] = t0.y
		}
		q.Push(*t0)

		t0.x = t.x - t.y - 1
		t0.y = t.y + 1
		if t0.x == target {
			ans = t0.y
			break
		}
		vis[t0.x] = t0.y
		if vis[t0.x] == 0 {
			vis[t0.x] = t0.y
		}
		q.Push(*t0)

	}

	return ans

}

func main() {
	var n int
	for {
		fmt.Scanf("%d", &n)
		fmt.Println(reachNumber(n))
	}

}
