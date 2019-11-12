/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-12
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

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
        int i;
        struct ListNode *n1, *n2;

        i = 0;
        n1 = head;
        n2 = head;

        while (n1 != NULL && i < n) {
                n1 = n1->next;
                i++;
        }
        if (i < n || n1 == NULL) {
                head = head->next;
                return head;
        }

        while (n1->next != NULL) {
                n1 = n1->next;
                n2 = n2->next;
        }

        n2->next = n2->next->next;
        return head;
}

int main() { return 0; }
