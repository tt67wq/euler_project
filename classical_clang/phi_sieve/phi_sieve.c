/*
 * =====================================================================================
 *
 *       Filename:  phi_sieve.c
 *
 *    Description:  欧拉计数函数筛子
 *
 *        Version:  1.0
 *        Created:  2019-06-27
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

#define MAX 40000000LL

typedef unsigned long ull;

ull SIEVE[MAX + 1] = {0};

void pre() {
        for (ull i = 1; i <= MAX; i++)
                SIEVE[i] = i;
        return;
}

char is_prime(ull n) {
        for (ull i = 2; i * i <= n; i++) {
                if (n % i == 0)
                        return 0;
        }
        return 1;
}

void sieve() {
        ull i = 2;
        for (; i * i <= MAX; i++) {
                if (is_prime(i)) {
                        for (ull j = i; j <= MAX; j += i) {
                                SIEVE[j] -= SIEVE[j] / i;
                        }
                }
        }
        for (; i <= MAX; i++) {
                if (SIEVE[i] == i) {
                        // prime
                        for (ull j = i; j <= MAX; j += i) {
                                SIEVE[j] -= SIEVE[j] / i;
                        }
                }
        }
}

void phi_chain(ull n) {
        while (n > 1) {
                printf("%ld => ", n);
                n = SIEVE[n];
        }
        printf("1\n");
}

int main(int argc, const char *argv[]) {
        pre();
        sieve();

        ull m;

        while (1) {
                printf("Enter a number: ");
                scanf("%ld", &m);
                phi_chain(m);
        }

        return 0;
}
