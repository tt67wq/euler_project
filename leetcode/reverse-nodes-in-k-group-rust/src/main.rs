// https://leetcode.cn/problems/reverse-nodes-in-k-group/

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

impl Solution {
    pub fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        let mut remain = head;
        let mut dummy = Box::new(ListNode::new(0));
        let mut tail = &mut dummy;

        while remain.is_some() {
            let (new_head, new_remain) = Solution::reverse_one(remain, k);
            remain = new_remain;
            tail.next = new_head;
            while tail.next.as_ref().is_some() {
                tail = tail.next.as_mut().unwrap();
            }
        }
        dummy.next
    }

    fn reverse_one(
        head: Option<Box<ListNode>>,
        k: i32,
    ) -> (Option<Box<ListNode>>, Option<Box<ListNode>>) {
        let mut pre = head.as_ref();
        for _ in 0..k {
            if pre.is_none() {
                return (head, None);
            }
            pre = pre.unwrap().next.as_ref();
        }

        let mut remain = head;
        let mut dummy = ListNode::new(0);
        for _ in 0..k {
            if let Some(mut node) = remain {
                remain = node.next.take();
                node.next = dummy.next;
                dummy.next = Some(node);
            }
        }

        (dummy.next, remain)
    }
}
