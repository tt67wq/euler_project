/*
 * =====================================================================================
 *
 *       Filename:  euler187.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "prime.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
        uint64_t index = 2;
        uint64_t counter = 0;
        while (1) {
                if (index > 50000000)
                        break;
                if (isPrime(index)) {
                        counter++;
                };
                index++;
        }
        printf("%llu\n", counter);

        return 0;
}
