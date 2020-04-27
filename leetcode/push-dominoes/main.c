/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-26
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

#define DEBUG 1
#define LOG(a)                                                                                     \
        if (DEBUG)                                                                                 \
                printf("%s\n", (a));

char *pushDominoes(char *dominoes) {
        int change = 0;
        int l = strlen(dominoes);
        do {
                change = 0;
                for (int i = 0; i < l; i++) {
                        if (i > 0 && dominoes[i] == 'L') {
                                if (dominoes[i - 1] == '.') {
                                        dominoes[i - 1] = 'l';
                                } else if (dominoes[i - 1] == 'r') {
                                        dominoes[i - 1] = '.';
                                } else {
                                        // pass
                                }
                        } else if (i + 1 < l && dominoes[i] == 'R') {
                                if (dominoes[i + 1] == '.') {
                                        dominoes[i + 1] = 'r';
                                } else if (dominoes[i + 1] == 'l') {
                                        dominoes[i + 1] = '.';
                                } else {
                                        // pass
                                }

                        } else {
                                //
                        }
                }
                for (int i = 0; i < l; i++) {
                        if (dominoes[i] == 'l') {
                                dominoes[i] = 'L';
                                change++;
                        } else if (dominoes[i] == 'r') {
                                dominoes[i] = 'R';
                                change++;
                        } else {
                                //
                        }
                }
                LOG(dominoes);

        } while (change > 0);

        return dominoes;
}

int main() {
        char a[] = ".L.R...LR..L..";
        printf("%s\n", pushDominoes(a));
        return 0;
}
