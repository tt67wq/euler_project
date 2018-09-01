/*
 * =====================================================================================
 *
 *       Filename:  euler_problem35.c
 *
 *    Description:  欧拉计划35题
 *
 *        Version:  1.0
 *        Created:  2018-08-31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 1000000

typedef unsigned long long ull;

// =====================  素数检测 ====================

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

int rotate(int num) {
        int r = num % 10;
        int d = num / 10;
        int t = d;
        int p = 0;
        while (t > 0) {
                t /= 10;
                p++;
        }
        return pow(10, p) * r + d;
}

int main() {
        clock_t begin = clock();
        int arr[LIMIT] = {0};
        for (int i = 2; i < LIMIT; i++) {
                if (probablyPrime(i, 3))
                        arr[i] = 1;
        }

        int jump[LIMIT] = {0};

        int count = 0;
        for (int i = 0; i < LIMIT; i++) {
                if (!arr[i])
                        continue;
                // check jump
                if (jump[i] == 1)
                        continue;
                int ps[6] = {0};
                int index = 1;
                ps[0] = i;

                int temp = rotate(i);
                int all_prime = 1;

                while (i != temp) {
                        if (!probablyPrime((ull)temp, 3)) {
                                all_prime = 0;
                                break;
                        }

                        ps[index++] = temp;
                        temp = rotate(temp);
                }
                if (all_prime == 0) {
                        arr[i] = 0;
                } else {
                        for (int j = 0; j < index; j++) {
                                if (j == 0)
                                        printf("%d ", ps[j]);
                                else
                                        printf(" ==> %d ", ps[j]);
                                jump[ps[j]] = 1;
                        }
                        printf("\n");
                }
        }

        for (int i = 0; i < LIMIT; i++)
                if (arr[i] == 1)
                        count++;

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", count, (double)(timespent / CLOCKS_PER_SEC));

        exit(EXIT_SUCCESS);
}
