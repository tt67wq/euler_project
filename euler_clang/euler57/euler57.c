/*
 * =====================================================================================
 *
 *       Filename:  euler57.c
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

#define SIZE 1000

typedef struct big_number {
        int *number;
        int size;
} big_num;

big_num *add(big_num *a, big_num *b) {
        big_num *result = (big_num *)malloc(sizeof(big_num));
        result->number = (int *)calloc(SIZE, sizeof(int));
        result->size = 0;
        int *begin = result->number;
        int *begin_a = a->number;
        int *begin_b = b->number;
        int *end_a = begin_a + a->size;
        int *end_b = begin_b + b->size;
        int carry = 0;
        while (begin_a != end_a || begin_b != end_b) {
                *begin = carry;
                if (begin_a != end_a) {
                        *begin += *begin_a;
                        ++begin_a;
                }
                if (begin_b != end_b) {
                        *begin += *begin_b;
                        ++begin_b;
                }

                carry = *begin / 10;
                *begin %= 10;
                ++begin;
                result->size++;
        }
        while (carry) {
                *begin = carry % 10;
                carry /= 10;
                result->size++;
                ++begin;
        }
        return result;
}

void print_num(big_num *a) {
        for (int i = a->size - 1; i >= 0; i--) {
                printf("%d", a->number[i]);
        }
        return;
}

void free_num(big_num *a) {
        free(a->number);
        free(a);
        return;
}

void copy(big_num *a, big_num *b) {
        b->size = a->size;
        for (int i = 0; i < a->size; i++)
                b->number[i] = a->number[i];
        free_num(a);
        return;
}

int main() {
        clock_t begin = clock();
        int counter = 0;

        big_num *a = (big_num *)malloc(sizeof(big_num));
        a->number = (int *)calloc(SIZE, sizeof(int));
        a->number[0] = 3;
        a->size = 1;

        big_num *b = (big_num *)malloc(sizeof(big_num));
        b->number = (int *)calloc(SIZE, sizeof(int));
        b->number[0] = 2;
        b->size = 1;

        for (int i = 1; i < 1000; i++) {
                big_num *t = add(b, b);
                big_num *c = add(a, t);
                big_num *d = add(a, b);

                copy(c, a);
                copy(d, b);

                free_num(t);

                if (a->size > b->size)
                        counter++;
        }

        printf("%d\n", counter);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
