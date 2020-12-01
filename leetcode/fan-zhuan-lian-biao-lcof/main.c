/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-12-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head) {
        struct ListNode *ptr0, *ptr1, *ptr2;
        ptr0 = NULL;
        ptr2 = NULL;
        ptr1 = head;

        while (ptr1 != NULL) {
                ptr2 = ptr1->next;
                ptr1->next = ptr0;
                ptr0 = ptr1;
                ptr1 = ptr2;
        }
        return ptr0;
}

int main() { return 0; }