/*
 * =====================================================================================
 *
 *       Filename:  euler55.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-08
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

#define LIMIT 50

unsigned long long rev_num(unsigned long long n) {
        unsigned long long t = n;
        unsigned long long r = 0;
        while (t) {
                r = r * 10 + t % 10;
                t = t / 10;
        }
        return r;
}

int palindrome(unsigned long long n) { return rev_num(n) == n; }

int lychrel(unsigned long long n) {
        int index = 0;
        while (index < LIMIT) {
                n = rev_num(n) + n;
                if (palindrome(n))
                        return 0;
                index++;
        }
        return 1;
}

int main() {
        clock_t begin = clock();

        int counter = 0;
        for (int i = 1; i < 10000; i++) {
                if (lychrel(i))
                        counter++;
        }
        printf("%d\n", counter);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
