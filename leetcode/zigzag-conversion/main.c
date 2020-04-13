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
        int wide = 0, idx = 0;
        char **matrix = (char **)calloc(numRows, sizeof(char *));
        for (int i = 0; i < numRows; i++) {
                matrix[i] = (char *)calloc(len, sizeof(char));
        }
        char *ans = (char *)malloc(sizeof(char) * (len + 1));

        matrix[0][0] = s[0];
        idx++;
        while (idx < len) {
                // down
                for (int row = 1; row < numRows; row++) {
                        matrix[row][wide] = s[idx++];
                }
                // up
                for (int row = numRows - 2; row >= 0; row--) {
                        matrix[row][++wide] = s[idx++];
                }
        }

#ifdef DEBUG
        printf("wide = %d\n", wide);
#endif
        idx = 0;
        for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < wide; col++) {
#ifdef DEBUG
                        printf("%c", matrix[row][col]);
#endif
                        if (matrix[row][col] != '\0') {
                                ans[idx++] = matrix[row][col];
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
        char *s = "PAYPALISHIRING";
        char *ans = convert(s, 3);
        printf("%s\n", ans);
        free(ans);
        return 0;
}
