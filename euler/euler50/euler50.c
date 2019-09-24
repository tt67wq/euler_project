/*
 * =====================================================================================
 *
 *       Filename:  euler50.c
 *
 *    Description:  欧拉计划50题
 *
 *        Version:  1.0
 *        Created:  2018-11-21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* #include "prime.h" */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TOP 1000000
#define LIMIT 1000

int isPrime(int n) {
        for (int i = 2; i <= sqrt(n); i++) {
                if (n % i == 0)
                        return 0;
        }
        return 1;
}

void find_prime_list(int *ps, int sum, int count, int *acc) {

        if (ps[0] == 0)
                return;
        if (sum > TOP)
                return;
        sum += *ps;
        count++;
        /* printf("%d, %d\n", *ps, sum); */
        if (isPrime(sum)) {
                /* printf(" ===> %d, %d\n", *ps, sum); */
                if (sum > *acc && sum <= TOP) {
                        acc[0] = sum;
                        acc[1] = count;
                }
        }
        find_prime_list(++ps, sum, count, acc);
}

int main() {
        clock_t begin = clock();
        int ps[LIMIT] = {0};
        int *psp = ps;
        int i = 2;
        int count = 0;
        while (1) {
                if (count == LIMIT)
                        break;
                if (isPrime(i)) {
                        *psp = i;
                        psp++;
                        count++;
                }
                i++;
        }

        int acc[2] = {0, 0};
        psp = ps;

        /* find_prime_list(psp, 0, 0, acc); */
        while (1) {
                if (*psp * acc[1] > TOP)
                        break;
                int bcc[2] = {0, 0};
                find_prime_list(psp, 0, 0, bcc);
                /* printf("%d => %d, %d\n", *psp, bcc[0], bcc[1]); */
                if (bcc[1] > acc[1]) {
                        acc[0] = bcc[0];
                        acc[1] = bcc[1];
                }
                psp++;
        }

        clock_t end = clock();
        double timespent = end - begin;

        printf("%d, %d\n", acc[0], acc[1]);
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
