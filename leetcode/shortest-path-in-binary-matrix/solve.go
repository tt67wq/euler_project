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

func shortestPathBinaryMatrix(grid [][]int) int {

	var l int = len(grid)

	if l == 1 {
		// 一个点的情况
		if grid[0][0] == 0 {
			return 1
		} else {
			return -1
		}
	}

	// 开头阻塞
	if grid[0][0] == 1 {
		return -1
	}

	// 结尾阻塞
	if grid[l-1][l-1] == 1 {
		return -1
	}

	type pos struct {
		x int
		y int
		s int
	}

	var q *Queue = new(Queue)
	var t, t1 *pos = new(pos), new(pos)
	var i, j, ans int
	var vis [][]int = make([][]int, l)

	for i = 0; i < l; i++ {
		vis[i] = make([]int, l)
	}

	t.x = 0
	t.y = 0
	t.s = 1
	q.Push(*t)
	vis[0][0] = 1
	ans = -1

	// bfs
	for q.Size() > 0 {
		*t = q.Pop().(pos)

		if t.x == l-1 && t.y == l-1 {
			ans = t.s
			break
		}
		for i = t.x - 1; i <= t.x+1; i++ {
			for j = t.y - 1; j <= t.y+1; j++ {
				// skip overbound
				if i < 0 || i >= l || j < 0 || j >= l {
					continue
				}
				// skip visited
				if vis[i][j] == 1 {
					continue
				}
				// skip block
				if grid[i][j] == 1 {
					continue
				}

				t1.x = i
				t1.y = j
				t1.s = t.s + 1

				vis[i][j] = 1
				q.Push(*t1)
			}
		}

	}

	return ans
}

func main() {
	fmt.Println(shortestPathBinaryMatrix([][]int{{0, 0, 1, 0, 1, 1}, {1, 0, 0, 1, 0, 0}, {0, 1, 0, 1, 0, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0}}))

	fmt.Println(shortestPathBinaryMatrix([][]int{{0, 0, 0, 0, 1}, {1, 0, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}}))
}
