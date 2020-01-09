package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseKGroup(head *ListNode, k int) *ListNode {
	if head == nil || k == 1 {
		return head
	}

	var h1, h2, p0, p1, p2 *ListNode
	var i int

	h1 = head

	for i = 0; i < k; i++ {
		if h1 != nil {
			h1 = h1.Next
		} else {
			return head
		}

	}

	h2 = reverseKGroup(h1, k)

	// reverse
	p0 = nil
	p1 = head

	// p0 -> p1 -> ...
	//       n1 -> n2 -> n3 -> ...

	for p1 != h1 {
		p2 = p1.Next
		if p0 == nil {
			p1.Next = h2
		} else {
			p1.Next = p0
		}
		p0 = p1
		p1 = p2
	}

	return p0
}

func main() {}
