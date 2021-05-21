/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  布隆过滤器测试
 *
 *        Version:  1.0
 *        Created:  2018-09-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bloom_filter.h"

unsigned int sax_hash(const char *key) {
        unsigned int h = 0;
        while (*key)
                h ^= (h << 5) + (h >> 2) + (unsigned char)*key++;
        return h;
}

unsigned int sdbm_hash(const char *key) {
        unsigned int h = 0;
        while (*key)
                h = (unsigned char)*key++ + (h << 6) + (h << 16) - h;
        return h;
}

int main() {
        BLOOM *bloom;

        if (!(bloom = bloom_create(2500000, 2, sax_hash, sdbm_hash))) {
                fprintf(stderr, "ERROR: Could not create bloom filter\n");
                return EXIT_FAILURE;
        }

        bloom_add(bloom, "aaa");
        bloom_add(bloom, "bbb");
        bloom_add(bloom, "ccc");

        printf("%d\n", bloom_check(bloom, "aaa"));
        printf("%d\n", bloom_check(bloom, "ddd"));

        return EXIT_SUCCESS;
}
