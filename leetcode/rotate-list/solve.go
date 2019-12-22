package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func rotateRight(head *ListNode, k int) *ListNode {
	if head == nil {
		return nil
	}

	if k == 0 {
		return head
	}

	var i, l int
	var tail, p1 *ListNode

	tail = head
	l = 1
	// find tail
	for tail.Next != nil {
		tail = tail.Next
		l++
	}

	for k > l {
		k -= l
	}

	k = l - k

	for i = 0; i < k; i++ {
		// fmt.Println("head: ", head, "tail: ", tail)
		// put head to tail
		p1 = head

		head = head.Next

		tail.Next = p1
		tail = tail.Next
		tail.Next = nil
	}

	return head
}

func main() {
	var h1, h2, ans *ListNode

	h1 = new(ListNode)
	h2 = new(ListNode)

	h1.Val = 1
	h2.Val = 2

	h1.Next = h2
	h2.Next = nil

	ans = rotateRight(h1, 5)
	for ans != nil {
		fmt.Println(ans.Val)
		ans = ans.Next
	}
}
