/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-27
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

bool canConstruct(char *s, int k) {
        int vis[26] = {0};
        int l = strlen(s);
        if (l == k) {
                return true;
        }
        if (l < k) {
                return false;
        }
        for (int i = 0; i < l; i++) {
                vis[s[i] - 'a']++;
        }

        int odd = 0, even = 0;

        for (int i = 0; i < 26; i++) {
                if (vis[i] > 0) {
#ifdef DEBUG
                        printf("%c => %d\n", i + 'a', vis[i]);
#endif
                        if ((vis[i] & 1) == 1) {
                                odd++;
                                even += (vis[i] - 1);
                        } else {
                                even += vis[i];
                        }
                }
        }
#ifdef DEBUG
        printf("odd => %d, even => %d\n", odd, even);
#endif

        if (odd > k || odd + even < k) {
                return false;
        }

        return true;
}

int main() {
        printf("%d\n", canConstruct("abcd", 4));
        return 0;
}
