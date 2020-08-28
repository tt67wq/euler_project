/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

int singleNumber(int *nums, int numsSize) {
        int a = 0, b = 0;

        for (int i = 0; i < numsSize; i++) {
                int c = nums[i];
                int tmpA = (a & ~b & ~c) | (~a & b & c);
                int tmpB = (~a & b & ~c) | (~a & ~b & c);
                a = tmpA;
                b = tmpB;
        }
        return a | b;
}

int main() { return 0; }