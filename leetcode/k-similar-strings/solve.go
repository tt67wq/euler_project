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

func kSimilarity(A string, B string) int {

	if A == B {
		return 0
	}

	type val struct {
		C     string
		steps int
	}

	var q *Queue = new(Queue)
	var t, t1 *val = new(val), new(val)
	var cache map[string]bool = make(map[string]bool)
	var i, j, L, d, md int
	var mfp string

	t.C = A
	t.steps = 0
	L = len(A)
	md = match_degree(A, B)

	cache[A] = true

	q.Push(*t)

	for q.Size() != 0 {
		*t = q.Pop().(val)
		for i = 0; i < L-1; i++ {
			for j = i + 1; j < L; j++ {
				if t.C[i] == t.C[j] {
					continue
				}
				mfp = swap(t.C, i, j)
				d = match_degree(mfp, B)
				if _, ok := cache[mfp]; ok {
					continue
				} else if d < md {
					continue
				} else if mfp == B {
					return t.steps + 1
				} else {
					t1.C = mfp
					t1.steps = t.steps + 1
					q.Push(*t1)
					cache[mfp] = true
					md = d
				}
			}
		}
	}

	return 0
}

func swap(A string, a, b int) string {
	var tmp byte
	var B []byte = []byte(A)
	tmp = B[a]
	B[a] = B[b]
	B[b] = tmp

	return string(B)
}

func match_degree(A, B string) int {
	var i, d int

	for i = 0; i < len(A); i++ {
		if A[i] == B[i] {
			d++
		}
	}
	return d
}

func main() {

	fmt.Println(kSimilarity("abccaacceecdeea", "bcaacceeccdeaae"))
}
