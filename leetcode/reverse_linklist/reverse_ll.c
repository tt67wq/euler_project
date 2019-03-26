/*
 * =====================================================================================
 *
 *       Filename:  reverse_ll.c
 *
 *    Description:
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

pnode reverse(pnode head) {
        pnode current = head;
        pnode next = NULL;
        pnode result = NULL;

        while (current != NULL) {
                next = current->next;
                current->next = result;
                result = current;
                current = next;
        }
        return result;
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

        struct node *rn = reverse(&n1);
        print_ll(rn);
        return 0;
}
