/*
 * =====================================================================================
 *
 *       Filename:  main.c
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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findClosest(char **words, int wordsSize, char *word1, char *word2) {
        int pre_a = -1, pre_b = -1, min = INT_MAX;
        for (int i = 0; i < wordsSize; i++) {
                if (strcmp(words[i], word1) == 0) {
                        pre_a = i;
                        if (pre_b != -1) {
                                min = min < (pre_a - pre_b) ? min : (pre_a - pre_b);
                        }
                } else if (strcmp(words[i], word2) == 0) {
                        pre_b = i;
                        if (pre_a != -1) {
                                min = min < (pre_b - pre_a) ? min : (pre_b - pre_a);
                        }
                }
        }
        return min;
}

int main() { return 0; }
