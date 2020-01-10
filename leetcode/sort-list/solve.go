package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func sortList(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	if head.Next == nil {
		return head
	}

	var h1 *ListNode
	h1 = splitList(head)
	// viewList(head)
	// viewList(h1)
	return mergeList(sortList(h1), sortList(head))
}

func mergeList(h1, h2 *ListNode) *ListNode {
	var h3, h4, tmp *ListNode

	for h1 != nil && h2 != nil {
		if h1.Val < h2.Val {
			if h3 == nil {
				h3 = new(ListNode)
				h3.Val = h1.Val
				h4 = h3
			} else {
				tmp = new(ListNode)
				tmp.Val = h1.Val
				h4.Next = tmp
				h4 = tmp
			}
			h1 = h1.Next
		} else {
			if h3 == nil {
				h3 = new(ListNode)
				h3.Val = h2.Val
				h4 = h3
			} else {
				tmp = new(ListNode)
				tmp.Val = h2.Val
				h4.Next = tmp
				h4 = tmp
			}
			h2 = h2.Next
		}
	}

	if h1 != nil {
		if h4 != nil {
			h4.Next = h1
		} else {
			return h1
		}

	} else {
		if h4 != nil {
			h4.Next = h2
		} else {
			return h2
		}
	}

	return h3
}

func splitList(head *ListNode) *ListNode {
	var h1, h2, h3 *ListNode

	h1 = head
	h2 = head
	h3 = nil

	for h2 != nil && h2.Next != nil {
		h3 = h1
		h1 = h1.Next
		h2 = h2.Next.Next
	}

	h3.Next = nil
	return h1
}

func viewList(head *ListNode) {
	for head != nil {
		fmt.Print(head.Val, "->")
		head = head.Next
	}
	fmt.Print("nil\n")
}

func main() {
	var a, b, c, d, e *ListNode

	a = new(ListNode)
	b = new(ListNode)
	c = new(ListNode)
	d = new(ListNode)
	e = new(ListNode)

	a.Val = 5
	b.Val = 2
	c.Val = 4
	d.Val = 1
	e.Val = 3

	a.Next = b
	b.Next = c
	c.Next = d
	d.Next = e

	viewList(sortList(a))
}
