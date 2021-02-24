/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-24
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxSatisfied(int *customers, int customersSize, int *grumpy, int grumpySize, int X) {
        int ans = 0, left = 0, tmp = 0, maxSave = 0;

        for (int i = 0; i < customersSize; i++) {
                if (grumpy[i] == 0) {
                        ans += customers[i];
                }
        }

        for (int i = left; i < left + X; i++) {
                if (grumpy[i]) {
                        tmp += customers[i];
                }
                maxSave = MAX(maxSave, tmp);
        }
        left += 1;

        for (; left + X - 1 < grumpySize; left++) {
                if (grumpy[left - 1]) {
                        tmp -= customers[left - 1];
                }
                if (grumpy[left + X - 1]) {
                        tmp += customers[left + X - 1];
                }
                // printf("%d\n", tmp);
                maxSave = MAX(maxSave, tmp);
        }
        return ans + maxSave;
}

int main() {
        int customers[] = {1, 0, 1, 2, 1, 1, 7, 5}, grumpy[] = {0, 1, 0, 1, 0, 1, 0, 1};
        int ans = maxSatisfied(customers, 8, grumpy, 8, 3);
        printf("%d\n", ans);
        return 0;
}