package main

import "fmt"

// ListNode node
type ListNode struct {
	Val  int
	Next *ListNode
}

func oddEvenList(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	var evenList *ListNode = new(ListNode)
	var evenListP *ListNode = evenList
	var headP *ListNode = head

	var prev *ListNode

	for head != nil {
		// fmt.Println("head", head.Val)
		prev = head
		head = head.Next

		if head != nil {
			prev.Next = head.Next
			evenList.Next = head
			evenList = evenList.Next
			head = head.Next
		} else {
			break
		}
	}
	evenList.Next = nil
	prev.Next = evenListP.Next

	return headP

}

func main() {
	node1 := ListNode{1, nil}
	node2 := ListNode{2, nil}
	node3 := ListNode{3, nil}
	node4 := ListNode{4, nil}
	node5 := ListNode{5, nil}

	node1.Next = &node2
	node2.Next = &node3
	node3.Next = &node4
	node4.Next = &node5

	res := oddEvenList(&node1)

	for res != nil {
		fmt.Println(res.Val)
		res = res.Next
	}
}
