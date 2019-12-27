/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-27
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

typedef struct _v4u {
        int vis[26];
        int remain;
} is3;

char *shortestCompletingWord(char *licensePlate, char **words, int wordsSize) {
        int i, j, n, idx, ms, esc[26];
        is3 *fob;
        char *ans;

        ans = NULL;
        bzero(esc, sizeof(int) * 26);
        n = 0;

        for (i = 0; i < strlen(licensePlate); i++) {
                if (licensePlate[i] >= 'a' && licensePlate[i] <= 'z') {
                        esc[licensePlate[i] - 'a']++;
                        n++;
                } else if (licensePlate[i] >= 'A' && licensePlate[i] <= 'Z') {
                        esc[licensePlate[i] - 'A']++;
                        n++;
                } else
                        // pass
                        ;
        }

        fob = (is3 *)calloc(wordsSize, sizeof(is3));

        for (i = 0; i < wordsSize; i++) {
                fob[i].remain = n;
                memcpy(fob[i].vis, esc, sizeof(int) * 26);
        }

        ms = 100000;
        for (i = 0; i < wordsSize; i++) {
                for (j = 0; j < strlen(words[i]); j++) {
                        if (words[i][j] >= 'A' && words[i][j] <= 'Z') {
                                idx = words[i][j] - 'A';
                        } else {
                                idx = words[i][j] - 'a';
                        }
                        if (fob[i].vis[idx] > 0) {
                                fob[i].vis[idx]--;
                                fob[i].remain--;
                                if (fob[i].remain == 0) {
                                        if (strlen(words[i]) < ms) {
                                                ms = strlen(words[i]);
                                                ans = words[i];
                                        }
                                        break;
                                }
                        }
                }
        }

        free(fob);
        return ans;
}

int main() { return 0; }
