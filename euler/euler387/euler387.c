/*
 * =====================================================================================
 *
 *       Filename:  euler387.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200000
#define MAX 1e5

typedef unsigned long long ull;
/*
srthp: short for strong, right truncatable Harshad prime
srth:  short for strong, right truncatable Harshad number

n is srthp
==>
n = 10 * m + k
  - n is prime
  - m is srth

---------------------
n is srth
==>
  - n is right truncatable
  - n / digit_sum(n) is prime

if n is Harshad number
  - try 10 times to check if 10*n+k is Harshad number
  - try 9 times to check if 10*n+k is srth

if n is srth
  - try 10 times to check 10*n+k is srthp

*/

bool isPrime(ull n) {
        if (n == 1)
                return 0;
        ull i;
        for (i = 2; i * i <= n; i++) {
                if (n % i == 0)
                        return false;
        }
        return true;
}

int digit_sum(ull n) {
        int s = 0;
        while (n > 0) {
                s += n % 10;
                n /= 10;
        }
        return s;
}

int main() {
        ull harshads[SIZE];
        ull harshads_copy[SIZE];
        ull srth[SIZE];
        ull srth_copy[SIZE];

        int d, i, j, k, a, b;
        int counter = 12;
        ull tmp, s = 0;

        memset(harshads, 0, sizeof(ull) * SIZE);
        memset(harshads_copy, 0, sizeof(ull) * SIZE);
        memset(srth_copy, 0, sizeof(ull) * SIZE);

        harshads[0] = 1;
        harshads[1] = 2;
        harshads[2] = 3;
        harshads[3] = 4;
        harshads[4] = 5;
        harshads[5] = 6;
        harshads[6] = 7;
        harshads[7] = 8;
        harshads[8] = 9;

        while (counter > 0) {
                i = 0;
                a = b = 0;
                while (harshads[i] != 0) {
                        for (j = 0; j < 10; j++) {
                                tmp = 10 * harshads[i] + j;
                                d = digit_sum(tmp);
                                if (tmp % d == 0) {
                                        harshads_copy[a++] = tmp;
                                        if (isPrime(tmp / d)) {
                                                srth_copy[b++] = tmp;
                                                for (k = 0; k < 10; k++) {
                                                        if (isPrime(10 * tmp + k)) {
                                                                printf("%lld\n", 10 * tmp + k);
                                                                s += (10 * tmp + k);
                                                        }
                                                }
                                        }
                                }
                        }
                        i++;
                }
                memcpy(harshads, harshads_copy, sizeof(ull) * SIZE);
                memcpy(srth, srth_copy, sizeof(ull) * SIZE);
                counter--;
        }
        printf("%llu\n", s);

        return 0;
}
