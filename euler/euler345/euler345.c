/*
 * =====================================================================================
 *
 *       Filename:  euler345.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 15

int matrix[N][N];
int matrix_copy[N][N];
int visc[N];

/*   7  53 183 439 863 497 383 563  79 (973) 287  63 343 169 583 */
/* 627 343 773 959 943 767 473 103 699 303 (957) 703 583 639 913 */
/* 447 283 463  29  23 487 463 (993) 119 883 327 493 423 159 743 */
/* 217 623   3 399 (853) 407 103 983  89 463 290 516 212 462 350 */
/* 960 376 682 (962) 300 780 486 502 912 800 250 346 172 812 350 */
/* (870) 456 192 162 593 473 915  45 989 873 823 965 425 329 803 */
/* 973 965 905 919 133 673 665 235 509 613 673 815 165 (992) 326 */
/* 322 148 (972) 962 286 255 941 541 265 323 925 281 601  95 973 */
/* 445 721  11 525 473  65 511 164 138 672  18 428 154 448 (848) */
/* 414 456 310 312 798 104 566 520 302 248 694 (976) 430 392 198 */
/* 184 829 373 181 631 101 (969) 613 840 740 778 458 284 760 390 */
/* 821 461 843 513  17 (901) 711 993 293 157 274  94 192 156 574 */
/*  34 124   4 878 450 476 712 914 838 669 875 299 (823) 329 699 */
/* 815 559 813 459 522 788 168 586 (966) 232 308 833 251 631 107 */
/* 813 (883) 451 509 615  77 281 613 459 205 380 274 302  35 805 */


void pre() {
        int i, j;
        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        if (matrix[i][j] > 700) {
                                matrix[i][j] = 0;
                        }
                }
        }
}

void dfs(int row, int *sum, int *max) {

        /* bzero(visr, sizeof(int) * N); */
        if (row >= N) {
                if (*sum > *max) {
                        *max = *sum;
                        printf("%d\n", *sum);
                }

                return;
        }

        int c;
        for (c = 0; c < N; c++) {
                if (visc[c] == 0 && matrix[row][c] == 0) {
                        visc[c] = 1;
                        (*sum) += matrix_copy[row][c];
                        dfs(row + 1, sum, max);
                        visc[c] = 0;
                        (*sum) -= matrix_copy[row][c];
                }
        }
}

int main() {
        int i;
        int sum = 0, max = 0;
        for (i = 0; i < N; i++) {
                scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2], &matrix[i][3], &matrix[i][4], &matrix[i][5], &matrix[i][6], &matrix[i][7],
                      &matrix[i][8], &matrix[i][9], &matrix[i][10], &matrix[i][11], &matrix[i][12], &matrix[i][13], &matrix[i][14]);
        }
        memcpy(matrix_copy, matrix, sizeof(int) * N * N);
        pre();
        bzero(visc, sizeof(int) * N);
        dfs(0, &sum, &max);
        return 0;
}
