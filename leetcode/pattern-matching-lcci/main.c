/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-22
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
#define MAX 1000

bool patternMatching(char *pattern, char *value) {
        int countA = 0, countB = 0;
        int lp = strlen(pattern), lv = strlen(value);
        if (lp == 0) {
                return (lv == 0);
        }
        for (int i = 0; i < lp; i++) {
                if (pattern[i] == 'a') {
                        countA++;
                } else {
                        countB++;
                }
        }

        bool flag = false;

        if (countB == 0) {
                // only 'a'
                for (int la = 0; la * countA <= lv; la++) {
                        char a[MAX] = "";
                        // match begin
                        int idx = 0;
                        for (int i = 0; i < lp; i++) {
                                if (strlen(a) == 0) {
                                        strncpy(a, value + idx, sizeof(char) * la);
                                        idx += la;
                                } else {
                                        if (strncmp(a, value + idx, sizeof(char) * la) != 0) {
                                                break;
                                        }
                                        idx += la;
                                }
                        }
                        if (idx == lv) {
                                flag = true;
#ifdef DEBUG
                                printf("a = %s, b = \"\"\n", a);
#endif
                                break;
                        }
                }
        } else if (countA == 0) {
                // only 'b'
                for (int lb = 0; lb * countB <= lv; lb++) {
                        char b[MAX] = "";
                        // match begin
                        int idx = 0;
                        for (int i = 0; i < lp; i++) {
                                if (strlen(b) == 0) {
                                        strncpy(b, value + idx, sizeof(char) * lb);
                                        idx += lb;
                                } else {
                                        if (strncmp(b, value + idx, sizeof(char) * lb) != 0) {
                                                break;
                                        }
                                        idx += lb;
                                }
                        }
                        if (idx == lv) {
                                flag = true;
#ifdef DEBUG
                                printf("a = \"\", b = %s\n", b);
#endif
                                break;
                        }
                }
        } else {
                // countA * x + countB * y = lv
                for (int la = 0; la * countA <= lv; la++) {
                        if ((lv - la * countA) % countB == 0) {
                                int lb = (lv - la * countA) / countB;

                                char a[MAX] = "", b[MAX] = "";
                                // match begin
                                int idx = 0;
                                for (int i = 0; i < lp; i++) {
                                        if (pattern[i] == 'a') {
                                                if (strlen(a) == 0) {
                                                        strncpy(a, value + idx, sizeof(char) * la);
                                                        idx += la;
                                                } else {
                                                        if (strncmp(a, value + idx,
                                                                    sizeof(char) * la) != 0) {
                                                                break;
                                                        }
                                                        idx += la;
                                                }
                                        } else {
                                                if (strlen(b) == 0) {
                                                        strncpy(b, value + idx, sizeof(char) * lb);
                                                        idx += lb;
                                                } else {
                                                        if (strncmp(b, value + idx,
                                                                    sizeof(char) * lb) != 0) {
                                                                break;
                                                        }
                                                        idx += lb;
                                                }
                                        }
                                }
                                if (idx == lv) {
                                        // match end
                                        if (la == lb && strcmp(a, b) == 0) {
                                                continue;
                                        }
                                        flag = true;
#ifdef DEBUG
                                        printf("a = %s, b = %s\n", a, b);
#endif
                                        break;
                                }

                        } else if (countB == 0) {

                        } else {
                                // pass
                        }
                }
        }
        return flag;
}

int main() {
        char pattern[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
             value[] = "";
        printf("%d\n", patternMatching(pattern, value));
        return 0;
}