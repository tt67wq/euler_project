package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseList(head *ListNode) *ListNode {
	var p0, p1 *ListNode

	p0 = nil
	p1 = head

	for p1 != nil {
		p2 := p1.Next
		p1.Next = p0
		p0 = p1
		p1 = p2
	}

	return p0
}

func main() {
	fmt.Println("--")
	return
}
