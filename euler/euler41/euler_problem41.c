/*
 * =====================================================================================
 *
 *       Filename:  euler_problem41.c
 *
 *    Description:  欧拉计划41题
 *
 *        Version:  1.0
 *        Created:  2018-09-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long ull;
typedef int bool;

const bool true = 1;
const bool false = 0;

// prime check

ull modMultiply(ull a, ull b, ull m) { return a * b % m; }

ull modPow(ull a, ull b, ull m) {
        ull v = 1;
        for (ull p = a % m; b > 0; b >>= 1, p = modMultiply(p, p, m))
                if (b & 1)
                        v = modMultiply(v, p, m);
        return v;
}

bool witness(ull a, ull n) {
        ull n1 = n - 1, s2 = n1 & -n1, x = modPow(a, n1 / s2, n);
        if (x == 1 || x == n1)
                return false;
        for (; s2 > 1; s2 >>= 1) {
                x = modMultiply(x, x, n);
                if (x == 1)
                        return true;
                if (x == n1)
                        return false;
        }
        return true;
}

ull random2(ull high) { return (ull)(high * (rand() / (double)RAND_MAX)); }

bool probablyPrime(ull n, int k) {
        if (n == 2 || n == 3)
                return 1;
        if (n < 2 || n % 2 == 0)
                return 0;
        while (k-- > 0)
                if (witness(random2(n - 3) + 2, n))
                        return false;
        return true;
}

int num_len(int num) {
        int len = 0;
        while (num) {
                len++;
                num /= 10;
        }
        return len;
}

int panditial(int num) {
        int len = num_len(num);
        int digits[10] = {0};
        while (num) {
                if (digits[num % 10 - 1] == 1)
                        return 0;
                digits[num % 10 - 1] = 1;
                num /= 10;
        }
        for (int i = 0; i < len; i++)
                if (digits[i] == 0)
                        return 0;
        return 1;
}
int list2num(int *list, int len) {
        int num = 0;
        for (int i = len - 1; i >= 0; i--) {
                num = num * 10 + list[i];
        }
        return num;
}

void perm(int deep, int n, int *array, int *results, int *is_used, int *mx) {
        int i;
        if (deep > n) // 越界递归结束
        {
                return;
        }

        if (deep == n) // 找到结果，打印，递归结束
        {
                int tmp = list2num(results, n);
                if (probablyPrime(tmp, 3)) {
                        /* printf("%d\n", tmp); */
                        *mx = *mx > tmp ? *mx : tmp;
                }

                return;
        }

        for (i = 0; i < n; i++) {
                if (is_used[i] == 0) {
                        is_used[i] = 1;
                        results[deep] = array[i];
                        perm(deep + 1, n, array, results, is_used, mx);
                        is_used[i] = 0;
                }
        }
}

int main() {
        clock_t begin = clock();
        int mx = 0;
        int array[] = {1, 2, 3, 4, 5, 6, 7};
        int is_used[7] = {0};
        int results[7] = {0};
        perm(0, 7, array, results, is_used, &mx);

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", mx, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
