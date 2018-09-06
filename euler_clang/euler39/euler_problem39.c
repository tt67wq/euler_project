/*
 * =====================================================================================
 *
 *       Filename:  euler_problem39.c
 *
 *    Description:  欧拉计划39题
 *
 *        Version:  1.0
 *        Created:  2018-09-06
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

#define LIMIT 1000

int gcd(int m, int n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int main() {
        clock_t begin = clock();
        int size = 200;
        int triangles[size][3];

        for (int i = 0; i < size; i++) {
                triangles[i][0] = 0;
                triangles[i][1] = 0;
                triangles[i][2] = 0;
        }

        int m = 2, n = 1;
        int index = 0;
        while (2 * (n * n + m * m) <= 2 * LIMIT) {
                if (n >= m) {
                        n = 1;
                        m++;
                        continue;
                }
                if ((m + n) % 2 == 0) {
                        n++;
                        continue;
                }
                if (gcd(m, n) != 1) {
                        n++;
                        continue;
                }
                triangles[index][0] = m * m - n * n;
                triangles[index][1] = 2 * m * n;
                triangles[index][2] = m * m + n * n;
                n++;
                index++;
        }
        int sums[2 * LIMIT] = {0};
        for (int i = 0; i < index; i++) {
                /* printf("%d ==> %d %d %d\n", i, triangles[i][0], triangles[i][1], triangles[i][2]); */
                int bs = triangles[i][0] + triangles[i][1] + triangles[i][2];
                int s = bs;
                while (s <= LIMIT) {
                        sums[s]++;
                        s += bs;
                }
        }

        int mx = 0;
        int mxi = 0;
        for (int i = 0; i < LIMIT; i++) {
                if (sums[i] > 0) {
                        mx = sums[i] > mx ? sums[i] : mx;
                        mxi = sums[i] == mx ? i : mxi;
                }
        }

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d perimeter => %d time use => %lfs\n", mxi, mx,
               (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
