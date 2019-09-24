/*
 * =====================================================================================
 *
 *       Filename:  euler183.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-13
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

void b_search(int n, double l, int s, int e, int *k) {
        if (e - s == 1) {
                *k = s * (l - log(s)) > e * (l - log(e)) ? s : e;
                return;
        }

        int mid = (s + e) / 2;
        double fm = l - log(mid) - 1;

        if (fm > 0)
                b_search(n, l, mid, e, k);
        else if (fm < 0)
                b_search(n, l, s, mid, k);
        else
                *k = mid;
}

int find_k(int n) {
        double l = log(n);
        int k = 0;
        b_search(n, l, 1, n, &k);
        return k;
}

int wipe(int n, int p) {
        while (1) {
                if (n % p)
                        return n;
                else
                        n /= p;
        }
}

int gcd(int m, int n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int d(n) {
        int k = find_k(n);
        int g = gcd(k, n);
        if (wipe(wipe(k / g, 2), 5) == 1)
                return -n;
        else
                return n;
}

int main() {
        double dtime = clock();
        long sum = 0;
        for (int i = 5; i < 10001; i++)
                sum += d(i);

        printf("%ld\n", sum);
        dtime = (double)(clock() - dtime) / CLOCKS_PER_SEC;
        printf("time=%.3lf sec.\n", dtime);

        return 0;
}
