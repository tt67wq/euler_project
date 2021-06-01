/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

//  

// 示例 1：

// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[1,2,3,6,9,8,7,4,5]
// 示例 2：

// 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// 输出：[1,2,3,4,8,12,11,10,9,5,6,7]
//  

// 提示：

// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 10
// -100 <= matrix[i][j] <= 100

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/spiral-matrix
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize) {
        if (matrixSize == 0) {
                *returnSize = 0;
                return NULL;
        }
        int *ans = (int *)calloc(matrixSize * matrixColSize[0], sizeof(int));
        *returnSize = matrixSize * matrixColSize[0];

        int _l = 0, index = 0;

        while (_l * 2 < matrixSize && _l * 2 < matrixColSize[0]) {
                // left 2 right
                for (int i = _l; i <= matrixColSize[0] - _l - 1 && index < *returnSize; i++) {
                        ans[index++] = matrix[_l][i];
                }

                // top 2 bottom
                for (int i = _l + 1; i < matrixSize - _l - 1 && index < *returnSize; i++) {
                        ans[index++] = matrix[i][matrixColSize[0] - 1 - _l];
                }

                // right 2 left
                for (int i = matrixColSize[0] - _l - 1; i > _l && index < *returnSize; i--) {
                        ans[index++] = matrix[matrixSize - 1 - _l][i];
                }

                // bottom 2 top
                for (int i = matrixSize - 1 - _l; i > _l && index < *returnSize; i--) {
                        ans[index++] = matrix[i][_l];
                }
                _l++;
        }

        return ans;
}

int main() {
        int _m1[] = {1, 2, 3, 4};
        int _m2[] = {5, 6, 7, 8};
        int _m3[] = {9, 10, 11, 12};

        int *matrix[] = {_m1, _m2, _m3};
        int colSize[] = {4};
        int returnSize;

        int *ans = spiralOrder(matrix, 3, colSize, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        puts("");
        return 0;
}