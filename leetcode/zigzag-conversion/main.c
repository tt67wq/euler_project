/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

char *convert(char *s, int numRows) {
        int len = strlen(s);
        char *ans = (char *)malloc(sizeof(char) * (len + 1));

        if (numRows == 1) {
                memcpy(ans, s, len * sizeof(char));
                ans[len] = '\0';
                return ans;
        }

        int wide = 0, idx = 0;
        char **matrix = (char **)calloc(numRows, sizeof(char *));
        for (int i = 0; i < numRows; i++) {
                matrix[i] = (char *)calloc(len, sizeof(char));
        }

        matrix[0][0] = s[0];
        idx++;
        while (idx < len) {
                // down
#ifdef DEBUG
                printf("idx = %d, wide = %d\n", idx, wide);
#endif
                for (int row = 1; row < numRows && idx < len; row++) {
                        matrix[row][wide] = s[idx++];
                }
#ifdef DEBUG
                printf("  idx = %d, wide = %d\n", idx, wide);
#endif
                // up
                for (int row = numRows - 2; row >= 0 && idx < len; row--) {
                        matrix[row][++wide] = s[idx++];
                }
        }

#ifdef DEBUG
        printf("wide = %d\n", wide);
#endif
        idx = 0;
        for (int row = 0; row < numRows; row++) {
                for (int col = 0; col <= wide; col++) {
                        if (matrix[row][col] != '\0') {
#ifdef DEBUG
                                printf("%c", matrix[row][col]);
#endif
                                ans[idx++] = matrix[row][col];
                        } else {
#ifdef DEBUG
                                printf(" ");
#endif
                        }
                }
#ifdef DEBUG
                printf("\n");
#endif
        }

        for (int i = 0; i < numRows; i++) {
                free(matrix[i]);
        }
        free(matrix);

        ans[idx] = '\0';

        return ans;
}

int main() {
        char *s = "AB";
        char *ans = convert(s, 1);
        printf("%s\n", ans);
        free(ans);
        return 0;
}
