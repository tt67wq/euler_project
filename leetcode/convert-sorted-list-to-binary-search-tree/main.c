/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。

// 本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

// 示例:

// 给定的有序链表： [-10, -3, 0, 5, 9],

// 一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

//       0
//      /
//    -3   9
//    /   /
//  -10  5

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct ListNode {
        int val;
        struct ListNode *next;
};

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

struct TreeNode *sortedListToBST(struct ListNode *head) {
        if (head == NULL) {
                return NULL;
        }

        if (head->next == NULL) {
                struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                root->val = head->val;
                root->left = NULL;
                root->right = NULL;
                return root;
        }

        struct ListNode *p0, *p1, *p2;

        p0 = head;
        p1 = head;

        while (p0 != NULL && p0->next != NULL) {
                p0 = p0->next->next;
                p2 = p1;
                p1 = p1->next;
        }
        struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        root->val = p1->val;
        root->right = sortedListToBST(p1->next);
        p2->next = NULL;
        root->left = sortedListToBST(head);

        return root;
}

int main() {
        struct ListNode n0, n1, n2, n3, n4;
        n0.val = -10;
        n1.val = -3;
        n2.val = 0;
        n3.val = 5;
        n4.val = 9;
        n0.next = &n1;
        n1.next = &n2;
        n2.next = &n3;
        n3.next = &n4;
        n4.next = NULL;

        sortedListToBST(&n0);

        return 0;
}