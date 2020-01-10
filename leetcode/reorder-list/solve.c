/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-01-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
        int val;
        struct ListNode *next;
};

void put_tail_to_next(struct ListNode *head) {

        struct ListNode *p1, *p2, *p3;
        p1 = head->next;
        p2 = head;
        p3 = NULL;

        // find tail
        while (p2->next != NULL) {
                p3 = p2;
                p2 = p2->next;
        }

        head->next = p2;
        p2->next = p1;

        if (p3 != NULL) {
                p3->next = NULL;
        }

        return;
}

void reorderList(struct ListNode *head) {
        if (head == NULL) {
                return;
        }
        if (head->next == NULL) {
                return;
        }
        if (head->next->next == NULL) {
                return;
        }

        struct ListNode *p1;

        p1 = head->next;
        put_tail_to_next(head);

        reorderList(p1);
}

int main() {
        struct ListNode a, b, c, d, e, *p;
        a.val = 1;
        b.val = 2;
        c.val = 3;
        d.val = 4;
        e.val = 5;

        a.next = &b;
        b.next = &c;
        c.next = &d;
        d.next = &e;
        e.next = NULL;

        reorderList(&a);
        // put_tail_to_next(&a);

        p = &a;
        while (p != NULL) {
                printf("%d ", p->val);
                p = p->next;
        }
        printf("\n");

        return 0;
}
