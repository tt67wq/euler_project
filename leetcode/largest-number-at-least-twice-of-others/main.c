/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-01-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
        int num;
        int idx;
} node;

int cmpfunc(const void *a, const void *b) {
        if (((node *)a)->num < ((node *)b)->num) {
                return 1;
        } else if (((node *)a)->num > ((node *)b)->num) {
                return -1;
        }
        return 0;
}

int dominantIndex(int *nums, int numsSize) {
        if (numsSize == 1) {
                return -1;
        }

        node *nodes = (node *)malloc(sizeof(node) * numsSize);
        for (int i = 0; i < numsSize; i++) {
                nodes[i].num = nums[i];
                nodes[i].idx = i;
        }

        qsort(nodes, numsSize, sizeof(node), cmpfunc);

        int res = -1;
        if (nodes[0].num >= nodes[1].num * 2) {
                res = nodes[0].idx;
        }

        free(nodes);

        return res;
}

int main() { return 0; }