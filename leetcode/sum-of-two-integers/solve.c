/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-31
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int getSum(int a, int b) {
        int sum, carry;
        sum = a ^ b;                        // 按位异或
        carry = ((unsigned int)a & b) << 1; // 按位与

        if (carry != 0) {
                return getSum(sum, carry);
        }
        return sum;
}

int main() {
        printf("%d\n", getSum(1, -1));
        printf("%d\n", getSum(1, 2));
        return 0;
}
