/*
 * =====================================================================================
 *
 *       Filename:  euler56.c
 *
 *    Description:  从thread里面抄来的答案
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

typedef struct big_number {
        int *number;
        int size;
} big_num;

big_num *initialize_big_num(int a, int b) {
        big_num *result = (big_num *)malloc(sizeof(big_num));
        result->number = (int *)calloc((int)ceil(b * log10(a)) + 1, sizeof(int));
        result->size = (int)log10(a) + 1;
        int *begin = result->number;
        while (a) {
                *begin = a % 10;
                a /= 10;
                ++begin;
        }
        return result;
}

big_num *exponentiation(int a, int b) {
        big_num *result = initialize_big_num(a, b);
        while (b > 1) {
                int carry = 0;
                int *begin = result->number;
                int *end = begin + result->size;
                while (begin != end) {
                        *begin = *begin * a + carry;
                        carry = *begin / 10;
                        *begin %= 10;
                        ++begin;
                }
                while (carry) {
                        *begin = carry % 10;
                        ++result->size;
                        carry /= 10;
                        ++begin;
                }
                --b;
        }
        return result;
}

int digit_sum(struct big_number **b_num) {
        int result = 0;
        int *begin = (*b_num)->number;
        int *end = begin + (*b_num)->size;
        while (begin != end) {
                result += *begin;
                ++begin;
        }
        free((*b_num)->number);
        free(*b_num);
        *b_num = NULL;
        return result;
}

int main(int argc, const char *argv[]) {

        int result = 0;
        int done = 0;
        for (int a = 99; a > 1; --a) {
                for (int b = 99; b > 1; --b) {
                        big_num *temp = exponentiation(a, b);
                        int sum = digit_sum(&temp);
                        int max_digit_sum = 9 * (b * log10(a) + 1);
                        if (sum > result)
                                result = sum;
                        if (max_digit_sum < result) {
                                done = 1;
                                break;
                        }
                }
                if (done)
                        break;
        }
        printf("Considering natural numbers of the form, a^b, where a, ");
        printf("b < 100, the maximum digital sum is %d\n", result);

        return 0;
}
