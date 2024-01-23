// https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}
//
impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

use std::cell::RefCell;
use std::rc::Rc;

pub struct Solution {}
impl Solution {
    fn dfs(
        node1: &Option<Rc<RefCell<TreeNode>>>,
        node2: &Option<Rc<RefCell<TreeNode>>>,
        depth: i32,
    ) {
        if let (Some(node1), Some(node2)) = (node1, node2) {
            let (mut node1, mut node2) = (node1.borrow_mut(), node2.borrow_mut());
            if depth & 1 == 1 {
                std::mem::swap(&mut node1.val, &mut node2.val);
            }
            Self::dfs(&node1.left, &node2.right, depth + 1);
            Self::dfs(&node1.right, &node2.left, depth + 1);
        }
    }

    pub fn reverse_odd_levels(
        root: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let tr = root.clone().unwrap();
        Self::dfs(&tr.brorow().left, &tr.borrow().right, 1);
        root
    }
}
