/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-25
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void print_bin(int number) {
        int bit = sizeof(int) * 8;
        int i;
        for (i = bit - 1; i >= 0; i--) {
                int bin = (number & (1 << i)) >> i;
                printf("%d", bin);
        }
        printf("\n");
}

// return next higher number with same number of bits set
unsigned int nextNumberWithSameBits(unsigned int x) {
        int smallest = x & (-x);
        int ripple = (int)x + smallest;
        int ones = ripple ^ x;

        return ((ones >> 2) / smallest) | ripple;
}

uint64_t fast(uint32_t maxDigit) {
        uint64_t result = 0;
        int digitSum = (maxDigit + 1) * maxDigit;
        int numDigits = 2 * (maxDigit + 1);

        uint64_t factorial = 1;
        for (uint32_t i = 1; i <= maxDigit + 1; i++) {
                factorial *= i;
        }
        uint64_t permutationRepeated[10];
        for (uint32_t i = 0; i < maxDigit + 1; i++) {
                permutationRepeated[i] = (factorial >> i);
        }

        uint32_t minBitmask = (1 << (maxDigit + 1)) - 1;
        uint32_t maxBitmask = minBitmask << (maxDigit + 1);

        for (uint32_t bitmask = minBitmask; bitmask <= maxBitmask;
             bitmask = nextNumberWithSameBits(bitmask)) {

                uint32_t reduce = bitmask;
                bool ok = true;
                while (reduce > 0) {
                        if ((reduce & 3) == 2) {
                                ok = false;
                                break;
                        }
                        reduce >>= 2;
                }
                if (!ok) {
                        continue;
                }
                // print_bin(bitmask);

                int sumOdd = 0;
                int repeated = 0;

                for (uint32_t pos = 0; pos < numDigits; pos++) {
                        if (bitmask & (1 << pos)) {
                                sumOdd += (pos / 2);

                                if (pos & 1) {
                                        repeated++;
                                }
                        }
                }

                if ((digitSum - 2 * sumOdd) % 11 == 0) {
                        result += (permutationRepeated[repeated] * permutationRepeated[repeated]);
                }
        }
        return result * maxDigit / (maxDigit + 1);
}

int main() {
        unsigned int x;
        scanf("%d", &x);
        uint64_t y = fast(x);
        printf("%lu\n", y);

        return 0;
}
