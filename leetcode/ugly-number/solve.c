/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

bool isUgly(int num) {
        if (num == 0)
                return false;
        while (1) {
                if (num % 2 == 0) {
                        num /= 2;
                        continue;
                }
                if (num % 3 == 0) {
                        num /= 3;
                        continue;
                }
                if (num % 5 == 0) {
                        num /= 5;
                        continue;
                }
                break;
        }
        return num == 1;
}

int main() { return 0; }
