
/*
 * =====================================================================================
 *
 *       Filename:  euler_problem11.c
 *
 *    Description:  欧拉计划11题
 *
 *        Version:  1.0
 *        Created:  2018-07-13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

// 构建方阵
int build_matrix(int **matrix) {

        char *lines[26] = {"01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01", "01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01",
                           "01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01", "01 01 01 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 01 01 01",
                           "01 01 01 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 01 01 01", "01 01 01 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 01 01 01",
                           "01 01 01 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 01 01 01", "01 01 01 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 01 01 01",
                           "01 01 01 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 01 01 01", "01 01 01 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 01 01 01",
                           "01 01 01 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 01 01 01", "01 01 01 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 01 01 01",
                           "01 01 01 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 01 01 01", "01 01 01 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 01 01 01",
                           "01 01 01 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 01 01 01", "01 01 01 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 01 01 01",
                           "01 01 01 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 01 01 01", "01 01 01 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 01 01 01",
                           "01 01 01 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 01 01 01", "01 01 01 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 01 01 01",
                           "01 01 01 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 01 01 01", "01 01 01 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 01 01 01",
                           "01 01 01 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48 01 01 01", "01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01",
                           "01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01", "01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01"};
        for (int i = 0; i < 26; i++) {
                /* printf("%s\n", lines[i]); */
                char *p;
                int j = 0;
                char str[strlen(lines[i]) + 1];
                strcpy(str, lines[i]);
                p = strtok(str, " ");
                matrix[i] = malloc(sizeof(int) * 26);
                while (p != NULL) {
                        /* printf("%d ", atoi(p)); */
                        matrix[i][j] = atoi(p);
                        j++;
                        p = strtok(NULL, " ");
                }
        }

        return 0;
}

int find_max(int *m, int *ls) {
        *m = 0;
        for (int i = 0; i < 8; i++) {
                *m = *m > ls[i] ? *m : ls[i];
        }
        return 0;
}

int main() {
        int **matrix;
        int maxm = 0;
        int tm = 0;
        clock_t begin = clock();
        build_matrix(matrix);
        int *ls = (int *)malloc(sizeof(int) * 8);
        for (int i = 3; i < 23; i++) {
                for (int j = 3; j < 23; j++) {
                        /* printf("%d ", ); */
                        ls[0] = matrix[i][j] * matrix[i - 1][j] * matrix[i - 2][j] * matrix[i - 3][j];
                        ls[1] = matrix[i][j] * matrix[i + 1][j] * matrix[i + 2][j] * matrix[i + 3][j];
                        ls[2] = matrix[i][j] * matrix[i][j - 1] * matrix[i][j - 2] * matrix[i][j - 3];
                        ls[3] = matrix[i][j] * matrix[i][j + 1] * matrix[i][j + 2] * matrix[i][j + 3];
                        ls[4] = matrix[i][j] * matrix[i + 1][j + 1] * matrix[i + 2][j + 2] * matrix[i + 3][j + 3];
                        ls[5] = matrix[i][j] * matrix[i - 1][j - 1] * matrix[i - 2][j - 2] * matrix[i - 3][j - 3];
                        ls[6] = matrix[i][j] * matrix[i - 1][j + 1] * matrix[i - 2][j + 2] * matrix[i - 3][j + 3];
                        ls[7] = matrix[i][j] * matrix[i + 1][j - 1] * matrix[i + 2][j - 2] * matrix[i + 3][j - 3];

                        find_max(&maxm, ls);
                        /* printf("%d => %d\n", matrix[i][j], maxm); */
                        tm = tm > maxm ? tm : maxm;
                };
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result: %d\nTime spent:%lfs", tm, (double)(timespent / CLOCKS_PER_SEC));
        // free
        free(ls);
        for (int i = 0; i < 26; i++)
                free(matrix[i]);
        return 0;
}