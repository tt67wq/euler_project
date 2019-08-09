/*
 * =====================================================================================
 *
 *       Filename:  financial_management.c
 *
 *    Description:   zoj 1048
 *
 *        Version:  1.0
 *        Created:  2019-08-09
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
        float b, s;
        int index = 12;
        s = 0;
        while (index > 0) {
                scanf("%f", &b);
                s += b;
                index--;
        }
        printf("$%.2f\n", s / 12.0);
        return 0;
}
