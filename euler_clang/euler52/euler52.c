/*
 * =====================================================================================
 *
 *       Filename:  euler52.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check(int num) {

        int numz[10] = {0};
        int swap, i;

        for (swap = num; swap != 0; swap /= 10)
                numz[swap % 10]++;

        for (i = 2; i <= 6; i++) {
                for (swap = num * i; swap != 0; swap /= 10)
                        if (!(numz[swap % 10]))
                                return 0;
        }
        return 1;
}

int main() {

        int i;

        for (i = 125874;; i++)
                if (check(i))
                        break;
        return printf("%d\n", i);
}
