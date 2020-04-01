/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item Item;
struct Item {
        char *gene;
        int step;
};

int one_diff(char *a, char *b) {
        int diff_c = 0;
        for (int i = 0; i < strlen(a) && diff_c < 2; i++) {
                if (a[i] != b[i]) {
                        diff_c++;
                }
        }
        return diff_c == 2 ? 0 : 1;
}

int minMutation(char *start, char *end, char **bank, int bankSize) {
        if (bankSize == 0) {
                return -1;
        }
        Item *e0 = (Item *)calloc(1, sizeof(Item));
        e0->gene = start;
        e0->step = 0;

        Item *queue = (Item *)calloc(bankSize * 2, sizeof(Item));
        int rear = 0;
        int front = 0;
        int *vis = (int *)calloc(bankSize, sizeof(int));
        int ans = -1;

        // push in
        queue[front++] = *e0;

        while (front != rear) {
                // pop
                Item e1 = queue[rear++];
                if (strcmp(e1.gene, end) == 0) {
                        ans = e1.step;
                        break;
                }

                // search one diff genes
                for (int i = 0; i < bankSize; i++) {
                        if (vis[i] == 1) {
                                continue;
                        }
                        if (one_diff(e1.gene, bank[i]) == 1) {
                                // push in
                                Item e2;
                                e2.gene = bank[i];
                                e2.step = e1.step + 1;
                                queue[front++] = e2;
                                vis[i] = 1;
                        }
                }
        }
        free(queue);
        free(vis);
        return ans;
}

int main() { return 0; }
