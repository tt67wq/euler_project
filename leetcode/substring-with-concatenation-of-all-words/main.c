/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-08
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

#define DEBUG
#define BASE 199291734240576784

bool isSubstr(unsigned long *powHash, unsigned long wordsHashSum, int wordsSize, int wordLen);

unsigned int jsHash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
        *returnSize = 0;
        int *ans = (int *)calloc(0xff, sizeof(int));
        if (!wordsSize || !words[0]) {
                return ans;
        }

        int wordLen = strlen(words[0]);
        int sLen = strlen(s);
        int substringLen = wordLen * wordsSize;

        unsigned long powHash[0xffff];
        unsigned long wordsHashSum = 0;

        for (int i = 0; i <= sLen - wordLen; i++) {
                int h = jsHash(s + i, wordLen);
                powHash[i] = (long)h * h;
        }

        for (int i = 0; i < wordsSize; i++) {
                int h = jsHash(words[i], wordLen);
                wordsHashSum += ((long)h * h);
                wordsHashSum %= BASE;
        }

        for (int i = 0; i <= sLen - substringLen; i++) {
                if (isSubstr(powHash + i, wordsHashSum, wordsSize, wordLen)) {
                        ans[(*returnSize)++] = i;
                }
        }
        return ans;
}

bool isSubstr(unsigned long *powHash, unsigned long wordsHashSum, int wordsSize, int wordLen) {
        unsigned long sHashSum = 0;

        for (int i = 0; i < wordsSize; i++) {
                sHashSum += powHash[i * wordLen];
                sHashSum %= BASE;
        }
        // printf("%ld %ld\n", sHashSum, wordsHashSum);
        return sHashSum == wordsHashSum;
}

int main() {
        // "barfoothefoobarman"
        // ["foo","bar"]
        char s[] = "barfoothefoobarman";
        int returnSize = 0;
        char word0[] = "foo";
        char word1[] = "bar";
        char *words[] = {word0, word1};

        int *ans = findSubstring(s, words, 2, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d\n", ans[i]);
        }
        free(ans);

        return 0;
}