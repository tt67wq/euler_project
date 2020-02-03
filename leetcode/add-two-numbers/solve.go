package main

import (
	"fmt"
)

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {

	var p int
	var head, acc, tmp *ListNode

	acc = new(ListNode)
	head = acc

	for l1 != nil || l2 != nil || p != 0 {
		tmp = new(ListNode)
		if l1 != nil {
			tmp.Val += l1.Val
			l1 = l1.Next
		}
		if l2 != nil {
			tmp.Val += l2.Val
			l2 = l2.Next
		}

		tmp.Val += p

		if tmp.Val > 9 {
			tmp.Val %= 10
			p = 1
		} else {
			p = 0
		}
		acc.Next = tmp
		acc = acc.Next
	}

	return head.Next
}

func main() {}
