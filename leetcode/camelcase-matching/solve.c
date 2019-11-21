/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool match(char *query, char *pattern) {
        int i, j, l1, l2;
        char a;

        i = 0;
        j = 0;
        l1 = strlen(query);
        l2 = strlen(pattern);

        while (j < l1 && i < l2) {
                a = pattern[i];

                while (j < l1 && query[j] != a) {
                        if (query[j] >= 'A' && query[j] <= 'Z')
                                break;
                        else
                                j++;
                }

                if (j == l1 || query[j] != a)
                        break;
                i++;
                j++;
        }

        if (i < l2)
                return false;

        if (j < l1) {
                while (j < l1) {
                        if (query[j] > 'A' && query[j] < 'Z') {
                                break;
                        } else {
                                j++;
                        }
                }
                if (j < l1)
                        return false;
        }
        return true;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool *camelMatch(char **queries, int queriesSize, char *pattern, int *returnSize) {
        int i;
        bool *ans;

        ans = (bool *)calloc(queriesSize, sizeof(bool));
        for (i = 0; i < queriesSize; i++)
                ans[i] = match(queries[i], pattern);
        *returnSize = queriesSize;
        return ans;
}

int main() {
        printf("%d\n", match("ControlPanel", "CooP"));
        return 0;
}
