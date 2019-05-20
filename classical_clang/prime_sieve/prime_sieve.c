#include "kvec.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef kvec_t(int) array;
typedef kvec_t(uint64_t) big_array;

//////////// prime tools //////////////
static inline bool is_in_sieve(char *sieve, uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void prime_sieve(uint64_t max, big_array *primes) {
        char *sieve = calloc(max / 16 + 1, 1);
        uint64_t max_sqrt = sqrt(max);
        for (uint64_t i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(sieve, i)) {
                        for (uint64_t j = i * i; j <= max; j += 2 * i) {
                                remove_from_sieve(sieve, j);
                        }
                }
        }

        kv_push(uint64_t, *primes, 2);
        for (uint64_t i = 3; i <= max; i += 2) {
                if (is_in_sieve(sieve, i))
                        kv_push(uint64_t, *primes, i);
        }

        free(sieve);
}

int main(int argc, char **argv) {
        big_array primes;
        kv_init(primes);

        prime_sieve(200, &primes);
        for (int j = 0; j < kv_size(primes); j++) {
                printf("%llu ", kv_A(primes, j));
        }
        printf("\n");

        return EXIT_SUCCESS;
}
