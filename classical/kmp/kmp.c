/*
 * =====================================================================================
 *
 *       Filename:  kmp.c
 *
 *    Description:  kmp算法 子串匹配
 *
 *        Version:  1.0
 *        Created:  2019-04-03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef kvec_t(char) string;

// 获取子串的部分匹配表
void get_next(string s, int *next) {
        int j = 0;
        int k = -1;
        next[0] = -1;
        while (j < kv_size(s) - 1) {
                if (k == -1 || s.a[j] == s.a[k]) {
                        j++;
                        k++;
                        next[j] = k;
                } else {
                        k = next[k];
                }
        }
        return;
}

int kmp_index(string s, string t, int *next) {
        int i = 0;
        int j = 0;
        while (i < (int)kv_size(s) && j < (int)kv_size(t)) {

                if (j == -1 || s.a[i] == t.a[j]) {
                        i++;
                        j++;
                } else {
                        j = next[j];
                }
        }

        if (j >= kv_size(t))
                return (i - (int)kv_size(t));
        return -1;
}

int main() {
        char s[] = "bbc abcdab abcdabcdabde";
        char t[] = "abcdabd";

        string seq1, seq2;
        kv_init(seq1);
        kv_init(seq2);

        for (int i = 0; s[i] != '\0'; i++) {
                kv_push(char, seq1, s[i]);
        }

        for (int i = 0; t[i] != '\0'; i++) {
                kv_push(char, seq2, t[i]);
        }

        int next[7] = {0};
        get_next(seq2, next);

        int index = kmp_index(seq1, seq2, next);
        printf("%d\n", index);

        return 0;
}
