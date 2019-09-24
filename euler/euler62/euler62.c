/*
 * =====================================================================================
 *
 *       Filename:  euler62.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table.h"

#define M 12

uint64_t solution(const int target) {
        uint64_t result = UINT64_MAX;
        ht *hash_table = initialize_hash_table(M);
        for (int i = 1; i < 10000; ++i) {
                insert(&hash_table, i);
        }
        it **begin = hash_table->bucket;
        it **end = begin + (1 << M);
        while (begin != end) {
                if (*begin) {
                        it *temp = *begin;
                        while (temp) {
                                if (temp->count == target && temp->data < result)
                                        result = temp->data;
                                temp = temp->next;
                        }
                }
                ++begin;
        }
        delete_hash_table(&hash_table);
        return result * result * result;
}

int main(int argc, const char *argv[]) {

        clock_t begin = clock();
        printf("The smallest cube for which exactly five permutations\n");
        printf("of its digits are cube: %llu\n", solution(5));
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
