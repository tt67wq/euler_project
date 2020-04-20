/*
 * =====================================================================================
 *
 *       Filename:  permutation_with_repeat.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-08
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

void bucketSort(char a[], int n, int max) {
        int *buckets = (int *)calloc(max, sizeof(int));

        // 1. 计数
        for (int i = 0; i < n; i++)
                buckets[a[i] - 'a']++;

        // 2. 排序
        {
                int i, j;
                for (i = 0, j = 0; i < max; i++) {
                        while ((buckets[i]--) > 0)
                                a[j++] = i + 'a';
                }
        }
        free(buckets);
}

void backtrack(char *S, int idx, char *acc, int *size) {

        int len = strlen(S);
        if (len == 0) {
                acc[idx] = '\0';
                printf("res: %s\n", acc);

                (*size)++;
                return;
        }

        for (int i = 0; i < len; i++) {
                if (i > 0 && S[i] == S[i - 1])
                        continue;
                acc[idx] = S[i];

                // kick out S[i]
                char *S1 = (char *)calloc(len, sizeof(char));
                {
                        int k = 0;
                        for (int j = 0; j < len; j++) {
                                if (j != i) {
                                        S1[k++] = S[j];
                                }
                        }
                        S1[k] = '\0';
                }
                backtrack(S1, idx + 1, acc, size);
                acc[idx] = 0;
                free(S1);
        }
}

void permutation(char *S, int *returnSize) {
        int l = strlen(S);

        // sort
        bucketSort(S, l, 26);

        char *acc = (char *)calloc(l + 1, sizeof(char));

        backtrack(S, 0, acc, returnSize);

        free(acc);

        return;
}

int main() {
        char s[] = "abb";
        int size = 0;
        permutation(s, &size);
        printf("size = %d\n", size);
        return 0;
}
