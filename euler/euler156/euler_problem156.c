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

#include "array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ull ten_base_count(int, int, int, ull *);

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
void binary_search(ull lower, ull higher, int base, ull *pows, A *res) {
        // 逃逸条件
        if (lower + 1 == higher) {
                if (count_digits2(lower, base, pows) == lower) {
                        /* printf("%llu\n", lower); */
                        if (append(res, lower))
                                ;
                        else
                                printf("insert %llu failed\n", lower);
                }

                return;
        }
        ull mid = (lower + higher) / 2;
        ull lower_value = count_digits2(lower, base, pows);
        ull higher_value = count_digits2(higher, base, pows);
        ull mid_value = count_digits2(mid, base, pows);

        if (mid_value >= lower && lower_value <= mid)
                binary_search(lower, mid, base, pows, res);
        if (mid_value <= higher && higher_value >= mid)
                binary_search(mid, higher, base, pows, res);
}

int main() {
	clock_t begin = clock();
        ull pows[13] = {0};
        for (int i = 0; i < 13; i++)
                pows[i] = (ull)pow(10, i);

        A *arr;
        initArr(arr, 1000);

        for (int i = 1; i < 10; i++)
		binary_search(1, pows[11], i, pows, arr);

        printf("binary search finished, total %d nums\n", arr->num);

	/* show_arr(arr); */
	ull sum = 0;
        for (int j = 0; j < arr->num; j++) {
                /* printf("%d ==> %llu\n", j, arr->head[j]); */
                sum += arr->head[j];
        }

	clock_t end = clock();
        double timespent = end - begin;

	printf("result => %llu, time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        free(arr->head);

        exit(EXIT_SUCCESS);
}
