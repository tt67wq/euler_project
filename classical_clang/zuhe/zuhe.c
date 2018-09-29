/*
 * =====================================================================================
 *
 *       Filename:  zuhe.c
 *
 *    Description:  计算组合数
 *
 *        Version:  1.0
 *        Created:  2018-09-29
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

#define MAX_FAC_NUM 100

// 质因数分解
void factorize(int num, int (*facs)[2], int *index) {
        int i;
        for (i = 2; i <= num; i++) {
                if (num % i == 0) {
                        num /= i;
                        int exists = 0;
                        for (int j = 0; j < *index; j++) {
                                if (facs[j][0] == i) {
                                        facs[j][1]++;
                                        exists = 1;
                                        break;
                                }
                        }
                        if (!exists) {
                                facs[*index][0] = i;
                                facs[*index][1] = 1;
                                (*index)++;
                        }
                        i--;
                }
        }
}

void factorize_map(int m, int n, int (*facs)[2], int *index) {
        for (int i = n; i > 0; i--)
                factorize(m--, facs, index);
}


// 乘方
int recursive_power(int m, int n) {
        int temp;

        if (n == 0) /* m^0 = 1                  */
                return 1;
        else if ((n & 0x01) == 0) { /* if power is even then */
                temp = recursive_power(m, n >> 1);
                return temp * temp; /* m^(2k) = (m^k)^2         */
        } else                      /* otherwise, m^n=m*m^(n-1) */
                return m * recursive_power(m, n - 1);
}

int main() {
        int facs1[MAX_FAC_NUM][2] = {{0}};
        int index1 = 0;

        int facs2[MAX_FAC_NUM][2] = {{0}};
        int index2 = 0;

        int m = 4;
        int n = 2;

        factorize_map(m, n, facs1, &index1);
        factorize_map(n, n, facs2, &index2);

        // minus
        for (int i = 0; i < index1; i++) {
                for (int j = 0; j < index2; j++) {
                        if (facs1[i][0] == facs2[j][0])
                                facs1[i][1] -= facs2[j][1];
                }
        }

        //
        int res = 1;
        for (int i = 0; i < index1; i++) {
                if (facs1[i][1] > 0) {
                        res *= recursive_power(facs1[i][0], facs1[i][1]);
                }
        }
        printf("%d\n", res);

        return 0;
}
