package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func detectCycle(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	if head.Next == nil {
		return nil
	}

	var p, c *ListNode

	p = head
	c = head.Next

	for c != nil {
		if c == p {
			return p
		}
		if loop_check(head, p, c) {
			return c
		}
		p = c
		c = c.Next
	}
	return nil
}

// from head to tail, check if any node equal to tem
func loop_check(head, tail, term *ListNode) bool {
	var t *ListNode

	t = head
	for t != tail {
		if t == term {
			return true
		}
		t = t.Next
	}
	return false
}

func main() {}
