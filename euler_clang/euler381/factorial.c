/*
 * =====================================================================================
 *
 *       Filename:  factorial.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

long extend_gcd(long a, long b) {
        long a1 = 0;
        long a2 = 1;

        long b1 = 1;
        long b2 = 0;

        long tmp, c;

        while (b != 0) {
                c = a / b;
                tmp = a;
                a = b;
                b = tmp % b;

                tmp = a1;
                a1 = a2 - c * a1;
                a2 = tmp;

                tmp = b1;
                b1 = b2 - c * b1;
                b2 = tmp;
        }
        return a2;
}

long niyuan(long a, long b) {
        long g = extend_gcd(a, b);
        return g > 0 ? g : b + g;
}

long factorial_mod(long n, long p) {
        long res = 1;
        while (n > 1) {
                res *= n;
                if (res >= p)
                        res %= p;
                if (res == 0)
                        break;
                n--;
        }
        return res;
}

long S2(long p) {
        int i;
        long t, s = (p - 1) / 2;
        for (i = 4; i < 6; i++) {
                t = factorial_mod(p - i, p);
                /* printf("(%ld - %d)! mod %ld = %ld\n", p, i, p, t); */
                s += t;
                if (s >= p)
                        s %= p;
        }
        return s;
}

long S(long p) {
        long t, s;
        s = (p - 1) / 2;
        t = (niyuan(p - 3, p) * s) % p;
        /* printf("(%ld - %d)! mod %ld = %ld\n", p, 3, p, */
        /* printf("(%ld - %d)! mod %ld = %ld\n", p, 4, p, t); */
        s += t;
        s += (niyuan(p - 4, p) * t) % p;
        return s % p;
}

int main() {
        long p;
        while (1) {
                scanf("%ld", &p);
                printf("%ld %ld\n", S(p), S2(p));
        }
        return 0;
}
