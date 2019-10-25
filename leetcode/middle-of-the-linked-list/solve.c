/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-25
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
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *middleNode(struct ListNode *head) {

        struct ListNode *mid;
        int i = 0;

        mid = head;
        while (head->next != NULL) {
                head = head->next;
                if ((++i) == 2) {
                        mid = mid->next;
                        i = 0;
                }
        }
        if (i == 1)
                mid = mid->next;
        return mid;
}
int main() { return 0; }
