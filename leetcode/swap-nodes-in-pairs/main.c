/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/* Definition for singly-linked list. */
struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *swapPairs(struct ListNode *head) {
        if (head == NULL) {
                return NULL;
        }
        struct ListNode *p0, *p1, *pt;

        p0 = NULL;
        p1 = head;
        pt = head;
        int count = 0;

        while (count < 2 && p1 != NULL) {
                p1 = p1->next;
                pt->next = p0;
                p0 = pt;
                pt = p1;
                count++;
        }

        head->next = swapPairs(p1);

        return p0;
}

int main() {
        struct ListNode n0, n1, n2, n3;
        n0.val = 1;
        n1.val = 2;
        n2.val = 3;
        n3.val = 4;

        n0.next = &n1;
        n1.next = &n2;
        n2.next = &n3;
        n3.next = NULL;

        struct ListNode *n4 = swapPairs(&n0);

        while (n4 != NULL) {
                printf("%d->", n4->val);
                n4 = n4->next;
        }
        printf("\n");
        return 0;
}
