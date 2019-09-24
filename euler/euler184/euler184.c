/*
 * =====================================================================================
 *
 *       Filename:  euler184.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printint64(unsigned long long int n) {
        unsigned long long int M = n;
        int digit[20], i, len;

        digit[0] = M % 10, M /= 10;
        for (i = 1; i < 20; i++)
                digit[i] = M % 10, M /= 10;
        len = 19;
        while ((len > 0) && (digit[len] == 0))
                len--;
        for (i = len; i >= 0; i--)
                printf("%d", digit[i]);

        return;
}

int gcd(int a, int b) {
        if (a < 0)
                a = -a;
        if (b < 0)
                b = -b;

        int c;

        while (b > 0) {
                if (a >= b) {
                        a -= b;
                        if (a >= b) {
                                a -= b;
                                if (a >= b) {
                                        a -= b;
                                        if (a >= b) {
                                                a -= b;
                                                if (a >= b) {
                                                        a -= b;
                                                        if (a >= b) {
                                                                a -= b;
                                                                if (a >= b) {
                                                                        a -= b;
                                                                        if (a >= b) {
                                                                                a -= b;
                                                                                if (a >= b)
                                                                                        a %= b;
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
                c = a, a = b, b = c;
        }
        return a;
}

int main() {

        int n, n2;
        int C[1200], F, i, i2, j;
        unsigned long long int N;

        while (1) {
                scanf("%d", &n);
                if (n > 1200)
                        printf("Too large!\n\n");
                else if (n < 1)
                        printf("Too small!\n\n");
                else {
                        double dtime = clock();

                        n2 = n * n;
                        F = 0;
                        for (i = 1; i < n; i++) {
                                F += 1 + (int)sqrt(n2 - 1 - i * i);
                        }
                        F *= 4;

                        for (i = 1; i < n; i++)
                                C[i] = 0;
                        for (i = -n + 1; i < n; i++) {
                                i2 = i * i, j = 0;
                                while (i2 + j * j < n2) {
                                        if (((i > 0) || (j > 0)) && (gcd(i, j) == 1)) {
                                                C[(int)sqrt((n2 - 1) / (i2 + j * j))]++;
                                        }
                                        j++;
                                }
                        }
                        printf("Number of points inside the circle=%d\n", F + 1);

                        N = 0;
                        for (i = 1; i < n; i++) {
                                for (j = i; j < n; j++) {
                                        if (i != j)
                                                N += (long long int)i * j * C[i] * C[j] * (F - 2 * i - 2 * j);
                                        else
                                                N += (long long int)i * i * C[i] * (C[i] - 1) * (F - 4 * i) / 2;
                                }
                        }
                        N /= 3;
                        dtime = clock() - dtime;
                        printf("Result=");
                        printint64(N);
                        printf(" triangles.\n");
                        printf("Time=%.3lf sec.\n\n", (double)dtime / CLOCKS_PER_SEC);
                }
        }
        return 0;
}
