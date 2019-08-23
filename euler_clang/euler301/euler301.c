/*
 * =====================================================================================
 *
 *       Filename:  euler301.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heap[3];

void print_heap(int step) { printf("%d: %d %d %d\n", step, heap[0], heap[1], heap[2]); }

int x(int step) {
        int winner = 0; // 1 for self, 0 for opponent
        int i, j;
        int heap_copy[3];
        print_heap(step);
        if (step % 2 == 0) {
                // self
                if (heap[0] == 0 && heap[1] == 0 && heap[2] == 0) {
                        return 0;
                }
                memcpy(heap_copy, heap, sizeof(heap_copy));
                for (i = 0; i < 3; i++) {
                        for (j = 1; j <= heap[i]; j++) {
                                heap[i] -= j;
                                if (x(step + 1) == 0) {
                                        memcpy(heap, heap_copy, sizeof(heap));
                                } else {
                                        winner = 1;
                                        break;
                                }
                        }
                        if (winner == 1)
                                break;
                }

        } else {
                // opponent
                if (heap[0] == 0 && heap[1] == 0 && heap[2] == 0) {
                        return 1;
                }
                memcpy(heap_copy, heap, sizeof(heap_copy));
                for (i = 0; i < 3; i++) {
                        for (j = 1; j <= heap[i]; j++) {
                                heap[i] -= j;
                                if (x(step + 1) == 1) {
                                        memcpy(heap, heap_copy, sizeof(heap));
                                } else {
                                        winner = 0;
                                        break;
                                }
                        }
                        if (winner == 0)
                                break;
                }
        }
        return winner;
}

int main() {
        while (1) {
                scanf("%d %d %d", &heap[0], &heap[1], &heap[2]);
                printf("%d\n", x(0));
        }
        return 0;
}
