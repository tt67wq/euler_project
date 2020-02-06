package main

import (
	"fmt"
)

type pos struct {
	x   int
	y   int
	dis int
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

func maxDistance(grid [][]int) int {
	var i, j, l, w, m int
	var cache [][]int
	var q *Queue
	var p, t *pos

	l = len(grid)
	w = len(grid[0])

	cache = make([][]int, l)

	for i = 0; i < l; i++ {
		cache[i] = make([]int, w)
	}

	q = new(Queue)
	p = new(pos)
	t = new(pos)

	for i = 0; i < l; i++ {
		for j = 0; j < w; j++ {
			if grid[i][j] == 1 {
				p.x = i
				p.y = j
				p.dis = 0
				q.Push(*p)
				cache[i][j] = 1
			}
		}
	}

	for q.size > 0 {
		*p = q.Pop().(pos)
		if p.dis > m {
			m = p.dis
		}
		// up
		if p.y > 0 && grid[p.x][p.y-1] == 0 && cache[p.x][p.y-1] == 0 {
			t.x = p.x
			t.y = p.y - 1
			t.dis = p.dis + 1
			q.Push(*t)
			cache[t.x][t.y] = 1
		}
		// down
		if p.y+1 < w && grid[p.x][p.y+1] == 0 && cache[p.x][p.y+1] == 0 {
			t.x = p.x
			t.y = p.y + 1
			t.dis = p.dis + 1
			q.Push(*t)
			cache[t.x][t.y] = 1
		}

		// left
		if p.x > 0 && grid[p.x-1][p.y] == 0 && cache[p.x-1][p.y] == 0 {
			t.x = p.x - 1
			t.y = p.y
			t.dis = p.dis + 1
			q.Push(*t)
			cache[t.x][t.y] = 1
		}
		// right
		if p.x+1 < l && grid[p.x+1][p.y] == 0 && cache[p.x+1][p.y] == 0 {
			t.x = p.x + 1
			t.y = p.y
			t.dis = p.dis + 1
			q.Push(*t)
			cache[t.x][t.y] = 1
		}

	}
	if m == 0 {
		return -1
	}
	return m
}

func main() {
	var grid [][]int

	grid = [][]int{{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}

	fmt.Println(maxDistance(grid))

}
