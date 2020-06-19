/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize) {
        if (matrixSize == 0) {
                (*returnSize) = 0;
                return NULL;
        }
        (*returnSize) = matrixSize * matrixColSize[0];
        int *ans = (int *)calloc((*returnSize), sizeof(int));

        int idx = 0;
        int level = 0;
        while (1) {
                // up: left to right
                for (int i = level; i < matrixColSize[level] - level; i++) {
                        ans[idx++] = matrix[level][i];
                }
                if (idx >= (*returnSize))
                        break;
#ifdef DEBUG
                printf("1, %d\n", idx);
#endif
                // right: head to bottom
                for (int i = level + 1; i < matrixSize - level; i++) {
                        ans[idx++] = matrix[i][matrixColSize[i] - level - 1];
                }
                if (idx >= (*returnSize))
                        break;
#ifdef DEBUG
                printf("2, %d\n", idx);
#endif
                // bottom: right to left
                for (int i = matrixColSize[level] - level - 2; i >= level; i--) {
                        ans[idx++] = matrix[matrixSize - level - 1][i];
                }
                if (idx >= (*returnSize))
                        break;
#ifdef DEBUG
                printf("3, %d\n", idx);
#endif
                // left: bottom to head
                for (int i = matrixSize - level - 2; i > level; i--) {
                        ans[idx++] = matrix[i][level];
                }
                if (idx >= (*returnSize))
                        break;
#ifdef DEBUG
                printf("4, %d\n", idx);
#endif
                level++;
        }
        return ans;
}

/* [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]] */

int main() {
        int l1[] = {1, 2, 3, 4};
        int l2[] = {5, 6, 7, 8};
        int l3[] = {9, 10, 11, 12};
        int l4[] = {13, 14, 15, 16};
        int *matrix[] = {l1, l2, l3, l4};
        int matrixColSize[] = {4, 4, 4, 4};
        int size;
        int *ans = spiralOrder(matrix, 4, matrixColSize, &size);
        for (int i = 0; i < size; i++) {
                printf("%d ", ans[i]);
        }
        printf("\n");
        free(ans);
        return 0;
}