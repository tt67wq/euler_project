/*
 * =====================================================================================
 *
 *       Filename:  euler347.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-12
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
#include <string.h>

#define MAX 10000000L

typedef unsigned long ul;

char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(ul idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(ul idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
        ul i, j;

        for (i = 3; i * i <= MAX; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i)
                                remove_from_sieve(j);
                }
        }
}

ul find_max(ul a, ul b, ul mx) {
        if (a * b > mx)
                return 0;
        int i, j;
        ul pa, m = 0;
        for (i = 1;; i++) {
                pa = (ul)pow(a, i);
                for (j = 1;; j++) {
                        pa *= b;
                        if (pa > mx) {
                                pa /= b;
                                j--;
                                break;
                        }
                }
                if (j == 0)
                        break;

                if (pa > m)
                        m = pa;
        }
        return m;
}

int main() {
        int c = 1;
        int i, j;
        ul ps[664580] = {0};
        ul t, s = 0;
        init();
        prime_sieve();
        ps[0] = 2;
        for (i = 3; i < MAX; i += 2) {
                if (is_in_sieve(i)) {
                        ps[c] = i;
                        c++;
                }
        }

        for (i = 0; ps[i] * ps[i] < MAX; i++) {
                for (j = i + 1; j < c; j++) {
                        t = find_max(ps[i], ps[j], MAX);
                        if (t == 0)
                                break;
                        /* printf("%ld %ld: %ld\n", ps[i], ps[j], t); */
                        s += t;
                }
        }

        printf("\n");
        printf("%ld\n", s);
        return 0;
}
