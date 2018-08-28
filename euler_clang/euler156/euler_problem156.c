/*
 * =====================================================================================
 *
 *       Filename:  euler_problem156.c
 *
 *    Description:  欧拉计划156题
 *
 *        Version:  1.0
 *        Created:  2018-08-23
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

typedef unsigned long long ull;
ull ten_base_count(int, int, int, ull *);

void count_digits(ull num, ull *counter) {
        while (num > 0) {
                counter[num % 10]++;
                num /= 10;
        }
}

ull count_digits2(ull num, int base, ull *pows) {
        ull tmp = num;
        int p = 0;
        ull count = 0;

        while (tmp > 0) {
                tmp /= 10;
                p++;
        }
        while (p >= 0) {
                ull n = pows[p];
                count += ten_base_count((int)(num / n), p, base, pows);
                if ((int)(num / n) == base)
                        count += num % n;
                num %= n;
                p--;
        }
        return count;
}

ull ten_base_count(int m, int n, int b, ull *pows) {
        if (m == 1) {
                if (b != 1)
                        return pows[n - 1] * n;
                else
                        return pows[n - 1] * n + 1;
        } else {
                if (m > b)
                        return pows[n - 1] * n * m + pows[n];
                else if (m == b)
                        return pows[n - 1] * n * m + 1;
                else
                        return pows[n - 1] * n * m;
        }
}

// 二分查找
void binary_search(ull lower, ull higher, int d, ull *res){
	
}

int main() {
        ull pows[13] = {0};

        /* ull sum = 0; */
        for (int i = 0; i < 13; i++)
                pows[i] = pow(10, i);

        for (ull i = 1; i <= pows[10]; i++) {
                ull num = i;
                int b = 1;

                ull tmp = count_digits2(num, b, pows);
        }

        /* printf("sum = %llu\n", sum); */

        return 0;
}
