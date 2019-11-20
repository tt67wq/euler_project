/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-20
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

int list2num(int *acc, int size) {
        int i, s = 0;
        for (i = 0; i < size; i++) {
                s *= 10;
                s += acc[i];
        }
        return s;
}

bool powerof2(int n) {
        while (n % 2 == 0)
                n >>= 1;
        return n == 1;
}

void perm(int deep, int n, int *array, int *acc, int *vis, bool *flag) {
        int i;
        // 越界递归结束
        if (deep > n)
                return;

        if (*flag)
                return;

        if (deep == n) {
                // 找到结果，递归结束
                if (acc[0] != 0 && acc[n - 1] % 2 == 0) {
                        if (powerof2(list2num(acc, n))) {
                                *flag = true;
                        }
                }
                return;
        }

        for (i = 0; i < n; i++) {
                if (vis[i] == 0) {
                        vis[i] = 1;
                        acc[deep] = array[i];
                        perm(deep + 1, n, array, acc, vis, flag);
                        vis[i] = 0;
                }
        }
}

int factorize(int n) {
        int s = 1;
        while (n > 0)
                s *= n--;
        return s;
}

bool reorderedPowerOf2(int N) {
        if (N == 1)
                return true;

        int n, i;
        int array[10], acc[10], vis[10];
        bool flag = false;

        i = 0;
        while (N > 0) {
                array[i++] = N % 10;
                N /= 10;
        }
        n = i;

        bzero(acc, sizeof(int) * 10);
        bzero(vis, sizeof(int) * 10);

        perm(0, n, array, acc, vis, &flag);

        return flag;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", reorderedPowerOf2(n));
        }

        return 0;
}
