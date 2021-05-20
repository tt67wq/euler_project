/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-20
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

// 矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素
// matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

// 请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。

//  

// 示例 1：

// 输入：matrix = [[5,2],[1,6]], k = 1
// 输出：7
// 解释：坐标 (0,1) 的值是 5 XOR 2 = 7 ，为最大的值。
// 示例 2：

// 输入：matrix = [[5,2],[1,6]], k = 2
// 输出：5
// 解释：坐标 (0,0) 的值是 5 = 5 ，为第 2 大的值。
// 示例 3：

// 输入：matrix = [[5,2],[1,6]], k = 3
// 输出：4
// 解释：坐标 (1,0) 的值是 5 XOR 1 = 4 ，为第 3 大的值。
// 示例 4：

// 输入：matrix = [[5,2],[1,6]], k = 4
// 输出：0
// 解释：坐标 (1,1) 的值是 5 XOR 2 XOR 1 XOR 6 = 0 ，为第 4 大的值。
//  

// 提示：

// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 1000
// 0 <= matrix[i][j] <= 10^6
// 1 <= k <= m * n

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/find-kth-smallest-xor-coordinate-value
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// struct heap {
//         int *array;
//         int size;
//         int capacity;
// };

// void swap(int *a, int *b) {
//         int temp = *b;
//         *b = *a;
//         *a = temp;
// }

// // Print the array
// void printArray(struct heap *hp) {
//         for (int i = 0; i < hp->size; ++i)
//                 printf("%d ", hp->array[i]);
//         printf("\n");
// }

// // Function to heapify the tree
// void heapify(struct heap *hp, int i) {
//         if (i >= hp->capacity) {
//                 return;
//         }
//         if (hp->size == 1) {
//                 // printf("Single element in the heap");
//         } else {
//                 // Find the smallest among root, left child and right child
//                 int smallest = i;
//                 int l = 2 * i + 1;
//                 int r = 2 * i + 2;
//                 if (l < hp->size && hp->array[l] < hp->array[smallest])
//                         smallest = l;
//                 if (r < hp->size && hp->array[r] < hp->array[smallest])
//                         smallest = r;

//                 // Swap and continue heapifying if root is not smallest
//                 if (smallest != i) {
//                         swap(&(hp->array[i]), &(hp->array[smallest]));
//                         heapify(hp, smallest);
//                 }
//         }
// }

// // Function to insert an element into the tree
// void insert(struct heap *hp, int newNum) {
//         if (hp->size == 0) {
//                 hp->array[0] = newNum;
//                 hp->size += 1;
//         } else if (hp->size < hp->capacity) {
//                 hp->array[hp->size] = newNum;
//                 hp->size += 1;
//                 for (int i = hp->size / 2 - 1; i >= 0; i--) {
//                         heapify(hp, i);
//                 }
//         } else {
//                 if (hp->array[0] < newNum) {
//                         hp->array[0] = newNum;
//                         for (int i = hp->size / 2 - 1; i >= 0; i--) {
//                                 heapify(hp, i);
//                         }
//                 }
//         }
// }
int cmpfunc(const void *a, const void *b) {
        if (*(int *)a < *(int *)b) {
                return 1;
        } else if (*(int *)a > *(int *)b) {
                return -1;
        }
        return 0;
}

int kthLargestValue(int **matrix, int matrixSize, int *matrixColSize, int k) {
        int **pre = (int **)calloc(matrixSize + 1, sizeof(int *));
        for (int i = 0; i < matrixSize + 1; i++) {
                pre[i] = (int *)calloc(matrixColSize[0] + 1, sizeof(int));
        }

        int *_list = (int *)calloc(matrixSize * matrixColSize[0], sizeof(int));
        int idx = 0;

        for (int i = 1; i <= matrixSize; i++) {
                for (int j = 1; j <= matrixColSize[0]; j++) {
                        pre[i][j] = pre[i - 1][j] ^ pre[i][j - 1] ^ pre[i - 1][j - 1] ^
                                    matrix[i - 1][j - 1];
                        _list[idx++] = pre[i][j];
                }
        }

        qsort(_list, idx, sizeof(int), cmpfunc);
        for (int i = 0; i < idx; i++) {
                printf("%d ", _list[i]);
        }
        puts("");

        return _list[k-1];
}

int main() {
        // [[10,9,5],[2,0,4],[1,0,9],[3,4,8]]
        // 10
        int c0[] = {10, 9, 5};
        int c1[] = {2, 0, 4};
        int c2[] = {1, 0, 9};
        int c3[] = {3, 4, 8};

        int *m[] = {c0, c1, c2, c3};
        int col[] = {sizeof(c0) / sizeof(int)};

        int ans = kthLargestValue(m, sizeof(m) / sizeof(m[0]), col, 10);
        printf("%d\n", ans);

        return 0;
}