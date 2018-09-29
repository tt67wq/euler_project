/*
 * =====================================================================================
 *
 *       Filename:  factor.c
 *
 *    Description:  因试分解
 *
 *        Version:  1.0
 *        Created:  2018-07-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

// 质因数分解
void factorize(int num, int (*facs)[2]) {
        int i;
        int index = 0;
        for (i = 2; i <= num; i++) {
                if (num % i == 0) {
                        num /= i;
                        int exists = 0;
                        for (int j = 0; j < index; j++) {
                                if (facs[j][0] == i) {
                                        facs[j][1]++;
                                        exists = 1;
                                        break;
                                }
                        }
                        if (!exists) {
                                facs[index][0] = i;
                                facs[index][1] = 1;
                                index++;
                        }
                        i--;
                }
        }
}

int main() {
        int facs[10][2] = {{0}};
        int len = 10;

        factorize(24, facs);

        for (int i = 0; i < len; i++) {
                if (facs[i][1] > 0)
                        printf("%d => %d\n", facs[i][0], facs[i][1]);
        }

        return 0;
}
