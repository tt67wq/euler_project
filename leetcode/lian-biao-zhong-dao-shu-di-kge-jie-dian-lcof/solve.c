/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-24
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *getKthFromEnd(struct ListNode *head, int k) {
        struct ListNode *p1, *p2;
        p1 = head;
        p2 = head;

        for (int i = 0; i < k && p2 != NULL; i++) {
                p2 = p2->next;
        }

        if (p2 == NULL) {
                return head;
        }

        while (p2 != NULL) {
                p1 = p1->next;
                p2 = p2->next;
        }

        return p1;
}

int main() { return 0; }
