/*
 * =====================================================================================
 *
 *       Filename:  1001.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-07-05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
        int a, b;
        while (scanf("%d %d", &a, &b) != EOF)
                printf("%d\n", a + b);

        return 0;
}
