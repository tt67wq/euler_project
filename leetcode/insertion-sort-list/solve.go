package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func insertionSortList(head *ListNode) *ListNode {

	var current, h, p, q *ListNode

	if head == nil {
		return head
	}

	h = head.Next
	head.Next = nil

	for h != nil {
		current = h
		h = h.Next

		// 寻找插入位置
		p = nil
		q = head
		for q != nil && q.Val <= current.Val {
			p = q
			q = q.Next
		}

		if q == head {
			head = current
		} else {
			p.Next = current
		}
		current.Next = q
	}
	return head
}

func main() {}
