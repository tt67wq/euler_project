/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-20
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **stringMatching(char **words, int wordsSize, int *returnSize) {

        char **ans = (char **)malloc(sizeof(char *) * wordsSize);
        int *vis = (int *)calloc(wordsSize, sizeof(int));
        *returnSize = 0;
        for (int i = 0; i < wordsSize; i++) {
                for (int j = i + 1; j < wordsSize; j++) {
                        if (strlen(words[i]) > strlen(words[j])) {
                                if (vis[j] == 0 && strstr(words[i], words[j]) != NULL) {
                                        ans[(*returnSize)++] = words[j];
                                        vis[j] = 1;
                                }
                        } else {
                                if (vis[i] == 0 && strstr(words[j], words[i]) != NULL) {
                                        ans[(*returnSize)++] = words[i];
                                        vis[i] = 1;
                                }
                        }
                }
        }
        free(vis);
        return ans;
}

int main() {
        char *words[] = {"evl",  "evlat", "kes",  "lwkesz",  "ckk",  "eylwkesz",
                         "efuw", "ickkw", "xnc",  "evlon",   "qsmd", "nmlwkeszk",
                         "uyh",  "xncme", "auze", "ixncmeqc"};
        int returnSize;

        char **ans = stringMatching(words, 16, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%s\n", ans[i]);
        }
        free(ans);

        return 0;
}
