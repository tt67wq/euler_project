package main

import (
	"fmt"
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

func main() {

	type val struct {
		x int
		y int
	}

	var q *Queue = new(Queue)
	var t *val = new(val)

	t.x = 1
	t.y = 2
	q.Push(*t)

	t.x = 3
	t.y = 4

	q.Push(*t)

	*t = q.Pop().(val)
	fmt.Println(*t)
	fmt.Println(q.Pop())
}
