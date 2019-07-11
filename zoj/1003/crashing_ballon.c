/*
 * =====================================================================================
 *
 *       Filename:  crashing_ballon.c
 *
 *    Description:  zoj 1003
 *
 *        Version:  1.0
 *        Created:  2019-07-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

 /* http://www.acmsearch.com/article/show/15 */
typedef unsigned long ul;

char possible_comb(ul n, int m, char *buff) {
        int i;
        for (i = m; i < 101; i++) {
                if (m > n)
                        break;
                if (n % i == 0) {
                        n /= i;
                        buff[i] = 1;
                }
        }
        if (n == 1)
                return 1;
        return 0;
}

int all_possible_comb(ul n, char *res[1000]) {
        int m;
        int index = 0;
        for (m = 1; m < 101; m++) {
                if (n % m == 0) {
                        char *buff = (char *)calloc(101, sizeof(char));
                        if (possible_comb(n, m, buff)) {
                                res[index++] = buff;
                        }
                }
        }
        return index;
}

void free_res(int counter, char *res[1000]) {
        int i;
        for (i = 0; i < counter; i++)
                free(res[i]);
}

int main() {

        /* FILE *fp; */
        /* fp = fopen("test.txt", "r"); */

        ul a, b, l, h, winner;
        int i, j, z, counter1, counter2;
        /* while (fscanf(fp, "%ld %ld", &a, &b) != EOF) { */
        /*         printf("%ld %ld\n", a, b); */
        while (scanf("%ld %ld", &a, &b) != EOF) {
                if (a == b) {
                        winner = a;
                        printf("%ld\n", winner);
                        continue;
                }

                l = a > b ? b : a;
                h = a > b ? a : b;

                char *res1[1000] = {NULL};
                char *res2[1000] = {NULL};
                counter1 = all_possible_comb(l, res1);
                if (counter1 == 0) {
                        winner = h;
                        printf("%ld\n", winner);
                        continue;
                }
                counter2 = all_possible_comb(h, res2);
                if (counter2 == 0) {
                        winner = l;
                        printf("%ld\n", winner);
                        continue;
                }

                char win = 0;
                for (i = 0; i < counter1; i++) {
                        char *buff1 = res1[i];
                        for (j = 0; j < counter2; j++) {
                                char *buff2 = res2[j];
                                char hit = 0;
                                for (z = 1; z < 101; z++) {
                                        if (buff2[z] == 1 && buff1[z] == 1) {
                                                hit = 1;
                                                break;
                                        }
                                }
                                if (hit) {
                                        continue;
                                } else {
                                        win = 1;
                                        break;
                                }
                        }
                        if (win) {
                                winner = h;
                                printf("%ld\n", winner);
                                break;
                        }
                }
                if (!win) {
                        winner = l;
                        printf("%ld\n", winner);
                }

                free_res(counter1, res1);
                free_res(counter2, res2);
        }
        /* fclose(fp); */
        return 0;
}
