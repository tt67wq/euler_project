/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-04
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

struct LinkNode {
        int val;
        struct LinkNode *next;
};
typedef struct LinkNode LinkNode;

void insert(LinkNode *head, int val);
void getAns(int *ans, LinkNode *rich, int *quiet, int i);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *loudAndRich(int **richer, int richerSize, int *richerColSize, int *quiet, int quietSize,
                 int *returnSize) {
        LinkNode *rich = (LinkNode *)calloc(quietSize, sizeof(LinkNode));

        for (int i = 0; i < quietSize; i++) {
                rich[i].val = -1;
                rich[i].next = NULL;
        }

        for (int i = 0; i < richerSize; i++) {
                insert(&rich[richer[i][1]], richer[i][0]);
        }

        int *ans = (int *)calloc(quietSize, sizeof(int));
        for (int i = 0; i < quietSize; i++) {
                ans[i] = -1;
        }

        for (int i = 0; i < quietSize; i++) {
                getAns(ans, rich, quiet, i);
        }
        (*returnSize) = quietSize;

        free(rich);
        return ans;
}

void insert(LinkNode *head, int val) {
        LinkNode *pt0 = head;
        while (pt0->next) {
                pt0 = pt0->next;
        }
        pt0->next = (LinkNode *)calloc(1, sizeof(LinkNode));
        pt0->next->val = val;
        pt0->next->next = NULL;
        return;
}

void getAns(int *ans, LinkNode *rich, int *quiet, int i) {
        if (ans[i] != -1) {
                return;
        }

        LinkNode *pt0 = &rich[i];
        int min = i;

        // dfs
        while (pt0->next) {
                pt0 = pt0->next;
                getAns(ans, rich, quiet, pt0->val);
                min = quiet[min] < quiet[ans[pt0->val]] ? min : ans[pt0->val];
        }
        ans[i] = min;
}

int main() { return 0; }