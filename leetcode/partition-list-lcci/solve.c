/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Definition for singly-linked list. */
struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *partition(struct ListNode *head, int x) {
        if (!head || !head->next)
                return head;
        struct ListNode *h1 = (struct ListNode *)malloc(sizeof(struct ListNode)), *t1 = h1;
        struct ListNode *h2 = (struct ListNode *)malloc(sizeof(struct ListNode)), *t2 = h2;
        t1->next = NULL;
        t2->next = NULL;
        while (head) {
                if (head->val < x) {
                        t1->next = head;
                        t1 = t1->next;
                } else {
                        t2->next = head;
                        t2 = t2->next;
                }
                head = head->next;
        }
        t1->next = h2->next;
        t2->next = NULL;
        return h1->next;
}
int main() { return 0; }
