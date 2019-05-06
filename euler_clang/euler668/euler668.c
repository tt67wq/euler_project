/*
 * =====================================================================================
 *
 *       Filename:  euler668.c
 *
 *    Description:  欧拉计划668题
 *
 *        Version:  1.0
 *        Created:  2019-05-05
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
#include <time.h>

#define LIMIT (uint64_t)1e10
#define MAX 1e12

typedef long long unsigned int uint64_t;

/* test whether the odd number idx is in the sieve */
static inline bool is_in_sieve(char *sieve, uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

int main(int argc, char **argv) {

        char *program_name = (argc > 0 ? argv[0] : "sieve");

        uint64_t limit = 0;
        /* limit = (uint64_t)atoi(argv[1]); */
        limit = LIMIT;
        uint64_t counter = limit;

        /* if we were lazy and careless, we'd just do max = atoi(argv[1]) */
        uint64_t max = limit;

        /* there are no primes smaller than 2 */
        if (max < 2)
                return EXIT_SUCCESS;

        /* make sure that j += 2*i and the sieve allocation cannot overflow */
        if (max > MAX - 2 * (uint64_t)sqrt(MAX) || max / 16 >= (size_t)-1) {
                fprintf(stderr, "%s: maximum %llu too large\n", program_name, max);
                return EXIT_FAILURE;
        }

        /* allocate the sieve array of (max+1)/16 bytes, rounded up */
        char *sieve = calloc(max / 16 + 1, 1);
        if (!sieve) {
                fprintf(stderr, "%s: failed to allocate %llu element sieve\n", program_name, max);
                return EXIT_FAILURE;
        }

        uint64_t max_sqrt = sqrt(max);

        for (uint64_t i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(sieve, i)) {
                        for (uint64_t j = i * i; j <= max; j += 2 * i) {
                                remove_from_sieve(sieve, j);
                        }
                }
        }

        /* puts("2"); /\* "2 is the oddest prime, because it's even" *\/ */

        for (uint64_t i = 3; i <= max; i += 2) {
                if (is_in_sieve(sieve, i)) {
                        /* printf("%llu\n", i); */
                        uint64_t j = i * i > max ? max / i : i;
                        counter -= j;
                }
        }

        free(sieve);

        printf("%llu\n", counter - 2);
        return 0;
}
