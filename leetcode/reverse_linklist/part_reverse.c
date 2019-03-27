/*
 * =====================================================================================
 *
 *       Filename:  part_reverse.c
 *
 *    Description:  链表部分求逆
 *
 *        Version:  1.0
 *        Created:  2019-03-26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
        int data;
        struct node *next;
};

typedef struct node *pnode;

pnode part_reverse(pnode head, int start, int end) {
        pnode current = head;
        pnode next = NULL;

        pnode n1 = NULL;
        pnode n2 = NULL;
        pnode n3 = NULL;
        /* pnode n4 = NULL; */

        int index = 0;

        while (head && (index < start)) {
                n1 = head;
                head = head->next;
                index++;
        }

        n2 = head;
        while (head && (index < end)) {
                next = head->next;
                head->next = n3;
                n3 = head;
                head = next;
        }

        n2->next = head;
        if (n1) {
                n1->next = n3;
        } else {
                current = n3;
        }

        return current;
}

void print_ll(pnode head) {
        while (head != NULL) {
                printf("%d=>", head->data);
                head = head->next;
        }
        printf("end\n");
        return;
}

int main() {
        struct node n1 = {1, NULL};
        struct node n2 = {2, NULL};
        struct node n3 = {3, NULL};
        struct node n4 = {4, NULL};
        struct node n5 = {5, NULL};

        n1.next = &n2;
        n2.next = &n3;
        n3.next = &n4;
        n4.next = &n5;
        print_ll(&n1);

        struct node *rn = part_reverse(&n1, 2, 4);
        print_ll(rn);
        return 0;
}
