/*
 * =====================================================================================
 *
 *       Filename:  euler58.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-11
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

int isprime(unsigned int num) {
        unsigned int lim = sqrt(num) + 1;

        if (num == 2 || num == 3)
                return 1;

        if (num < 2 || num % 2 == 0 || num % 3 == 0)
                return 0;

        for (unsigned int i = 5; i <= lim; i += 6)
                if (num % i == 0 || num % (i + 2) == 0)
                        return 0;

        return 1;
}

int main() {
        clock_t begin = clock();
        int numprimes = 3; // 3, 5, 7 in second layer
        int numnums = 5;
        int i;

        for (i = 5; numprimes * 10 >= numnums; i += 2) {
                int lr_corner = i * i;

                for (int j = 1; j <= 3; j++)
                        if (isprime(lr_corner - j * (i - 1)))
                                numprimes++;

                numnums += 4;
        }

        printf("%d\n", i - 2);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
