#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/next-greater-node-in-linked-list/

from typing import List, Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        ans = []
        s = []  # 单调栈

        cur = head
        idx = -1

        while cur:
            idx += 1
            ans.append(0)

            while s and s[-1][0] < cur.val:  # 栈顶元素小于当前元素
                _, i = s.pop()  # 弹出栈顶元素
                ans[i] = cur.val

            # 栈顶元素大于当前元素，入栈
            s.append((cur.val, idx))
            cur = cur.next

        return ans


def test_nextLargerNodes():
    # Test case 1
    head = ListNode(2, ListNode(1, ListNode(5)))
    expected_output = [5, 5, 0]
    assert Solution().nextLargerNodes(head) == expected_output

    # Test case 2
    head = ListNode(2, ListNode(7, ListNode(4, ListNode(3, ListNode(5)))))
    expected_output = [7, 0, 5, 5, 0]
    assert Solution().nextLargerNodes(head) == expected_output

    # Test case 3
    head = None
    expected_output = []
    assert Solution().nextLargerNodes(head) == expected_output

    # Test case 4
    head = ListNode(1)
    expected_output = [0]
    assert Solution().nextLargerNodes(head) == expected_output


def main():
    test_nextLargerNodes()


if __name__ == "__main__":
    main()
