/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int *owxxoy(int *cont, int index, int l) {
        int *ans, *xck;

        xck = (int *)calloc(2, sizeof(int));
        if (index == l - 1) {
                xck[0] = cont[index];
                xck[1] = 1;
                return xck;
        }
        ans = owxxoy(cont, index + 1, l);

        xck[0] = cont[index] * ans[0] + ans[1];
        xck[1] = ans[0];

        return xck;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *fraction(int *cont, int contSize, int *returnSize) {
        *returnSize = 2;
        return owxxoy(cont, 0, contSize);
}

int main() {
        int cont[3] = {0, 0, 3};
        int *ans;
        ans = owxxoy(cont, 0, 3);
        printf("%d %d\n", ans[0], ans[1]);
        return 0;
}
