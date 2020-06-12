/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MATCH_CURR 1
#define MATCH_LEFT 2
#define MATCH_UP 3

void initArray(int ***array, int row, int col) {
        int mSize = sizeof(int) * row * col;
        int *bigMem = (int *)malloc(mSize);
        memset(bigMem, 0, mSize);

        (*array) = (int **)malloc(sizeof(int *) * row);

        for (int i = 0; i < row; i++) {
                (*array)[i] = &(bigMem[i * col]);
        }
}

void updateMatchCount(int **match, int **count, char *str1, char *str2, int row, int col) {
        for (int i = 0; i < row - 1; i++) {
                for (int j = 0; j < col - 1; j++) {
                        if (str1[i] == str2[j]) {
                                count[i + 1][j + 1] = count[i][j] + 1;
                                match[i][j] = MATCH_CURR;
                        } else if (count[i + 1][j] >= count[i][j + 1]) {
                                count[i + 1][j + 1] = count[i + 1][j];
                                match[i][j] = MATCH_LEFT;
                        } else {
                                count[i + 1][j + 1] = count[i][j + 1];
                                match[i][j] = MATCH_UP;
                        }
                }
        }
}

void getStrByMatchInfo(char *result, int **match, int **count, char *str1, char *str2, int row,
                       int col) {
        int outLen = row + col - 2 - count[row - 1][col - 1];
        result[outLen] = '\0';

        int i, j, k;

        for (i = row - 2, j = col - 2, k = outLen - 1; j >= 0 && i >= 0;) {
                if (match[i][j] == MATCH_CURR) {
                        result[k--] = str1[i];
                        i--;
                        j--;
                } else if (match[i][j] == MATCH_LEFT) {
                        result[k--] = str2[j];
                        j--;
                } else {
                        result[k--] = str1[i];
                        i--;
                }
        }
        while (i >= 0) {
                result[k--] = str1[i--];
        }

        while (j >= 0) {
                result[k--] = str2[j--];
        }
}

char *shortestCommonSupersequence(char *str1, char *str2) {
        if (str1 == NULL && str2 == NULL) {
                return NULL;
        }

        int **count; // count[i][j] -> how many letters match between {str1[:i) str2[:j)}
        int **match; // match[i][j] -> last match direction on {str1[i], str2[j]}
        int row = strlen(str1) + 1;
        int col = strlen(str2) + 1;

        char *result = (char *)malloc(sizeof(char) * (row + col));

        // TODO: memery detect
        initArray(&match, row, col);
        initArray(&count, row, col);

        updateMatchCount(match, count, str1, str2, row, col);

#ifdef DEBUG
        for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                        printf("%d ", count[i][j]);
                }
                printf("\n");
        }
        printf("-----------------------\n");
        for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                        printf("%d ", match[i][j]);
                }
                printf("\n");
        }

#endif

        getStrByMatchInfo(result, match, count, str1, str2, row, col);

        free(match[0]);
        free(count[0]);
        free(match);
        free(count);

        return result;
}

int main() {
        char *str1 = "abac";
        char *str2 = "cab";

        printf("str1 : %s\n", str1);
        printf("str2 : %s\n", str2);
        printf("-----------------------\n");
        char *str3 = shortestCommonSupersequence(str1, str2);
        printf("%s\n", str3);

        free(str3);
        return 0;
}
