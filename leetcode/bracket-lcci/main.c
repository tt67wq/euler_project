/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-31
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

#define DEBUG

void dfs(int n, int left, int right, char **res, char *tmp, int *returnSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
        if (n == 1) {
                char **ans = (char **)malloc(sizeof(char *));
                ans[0] = "()";
                (*returnSize) = 1;
                return ans;
        }

        char **ans = (char **)calloc(sizeof(char *), 10000);
        char *tmp = (char *)calloc(sizeof(char), (2 * n + 1));
        (*returnSize) = 0;
        dfs(n, 0, 0, ans, tmp, returnSize);
        free(tmp);
        return ans;
}

void dfs(int n, int left, int right, char **res, char *tmp, int *returnSize) {
        if (left == n && left == right) {
                char *_res = (char *)calloc(sizeof(char), (2 * n + 1));
                strcpy(_res, tmp);
                res[(*returnSize)++] = _res;
                return;
        }

        if (left + 1 <= n) {
                char *newTmp = (char *)calloc(sizeof(char), (2 * n + 1));
                strcpy(newTmp, tmp);
                dfs(n, left + 1, right, res, strcat(newTmp, "("), returnSize);
                free(newTmp);
        }
        if (right + 1 <= left) {
                char *newTmp = (char *)calloc(sizeof(char), (2 * n + 1));
                strcpy(newTmp, tmp);
                dfs(n, left, right + 1, res, strcat(newTmp, ")"), returnSize);
                free(newTmp);
        }
}

int main() {
        int returnSize = 0;
        char **res = generateParenthesis(3, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%s\n", res[i]);
                free(res[i]);
        }
        free(res);
        return 0;
}