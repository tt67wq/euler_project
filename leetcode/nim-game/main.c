/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-18
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
#define MAX 10000

char CACHE[MAX];

bool _canWinNim(int n) {
        if (n == 0) {
                return false;
        }
        if (n < 4) {
                return true;
        }
        if (CACHE[n] > 0) {
                return CACHE[n] == 1;
        }

        bool canWin = false;
        for (int i = 1; i < 4; i++) {
                // can opponent win?
                if (!_canWinNim(n - i)) {
                        canWin = true;
                }
        }
        CACHE[n] = canWin ? 1 : 2;
        return canWin;
}

bool canWinNim2(int n) {
        memset(CACHE, 0, sizeof(char) * MAX);
        return _canWinNim(n);
}

bool canWinNim(int n) { return n % 4 != 0; }

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d, %d\n", canWinNim2(n), canWinNim(n));
        }

        return 0;
}