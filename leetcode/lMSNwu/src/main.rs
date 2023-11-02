// https://leetcode.cn/problems/lMSNwu/description/

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

pub struct Solution {}

impl Solution {
    pub fn add_two_numbers(
        l1: Option<Box<ListNode>>,
        l2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let mut a = vec![];
        let mut b = vec![];
        let mut root = l1;
        while let Some(node) = root {
            a.push(node.val);
            root = node.next;
        }
        let mut root = l2;
        while let Some(node) = root {
            b.push(node.val);
            root = node.next;
        }
        let mut ans = None;
        let mut carry = 0;
        while !a.is_empty() || !b.is_empty() {
            carry += a.pop().unwrap_or(0) + b.pop().unwrap_or(0);
            ans = Some(Box::new(ListNode {
                val: carry % 10,
                next: ans,
            }));
            carry /= 10;
        }
        if carry > 0 {
            ans = Some(Box::new(ListNode {
                val: carry,
                next: ans,
            }));
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add_two_numbers() {
        // Test case 1: Both lists are empty
        assert_eq!(Solution::add_two_numbers(None, None), None);

        // Test case 2: One list is empty, the other is not
        let l1 = Some(Box::new(ListNode { val: 2, next: None }));
        let l2 = None;
        let expected = Some(Box::new(ListNode { val: 2, next: None }));
        assert_eq!(Solution::add_two_numbers(l1, l2), expected);

        // Test case 3: Both lists have one node
        let l1 = Some(Box::new(ListNode { val: 2, next: None }));
        let l2 = Some(Box::new(ListNode { val: 3, next: None }));
        let expected = Some(Box::new(ListNode { val: 5, next: None }));
        assert_eq!(Solution::add_two_numbers(l1, l2), expected);

        // Test case 4: Both lists have multiple nodes
        let l1 = Some(Box::new(ListNode {
            val: 2,
            next: Some(Box::new(ListNode {
                val: 4,
                next: Some(Box::new(ListNode { val: 3, next: None })),
            })),
        }));
        let l2 = Some(Box::new(ListNode {
            val: 5,
            next: Some(Box::new(ListNode {
                val: 6,
                next: Some(Box::new(ListNode { val: 4, next: None })),
            })),
        }));
        let expected = Some(Box::new(ListNode {
            val: 8,
            next: Some(Box::new(ListNode {
                val: 0,
                next: Some(Box::new(ListNode { val: 7, next: None })),
            })),
        }));
        assert_eq!(Solution::add_two_numbers(l1, l2), expected);
    }
}
