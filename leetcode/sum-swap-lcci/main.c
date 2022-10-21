/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定两个整数数组，请交换一对数值（每个数组中取一个数值），使得两个数组所有元素的和相等。

// 返回一个数组，第一个元素是第一个数组中要交换的元素，第二个元素是第二个数组中要交换的元素。
// 若有多个答案，返回任意一个均可。若无满足条件的数值，返回空数组。

// 示例:

// 输入: array1 = [4, 1, 2, 1, 1, 2], array2 = [3, 6, 3, 3]
// 输出: [1, 3]
// 示例:

// 输入: array1 = [1, 2, 3], array2 = [4, 5, 6]
// 输出: []
// 提示：

// 1 <= array1.length, array2.length <= 100000

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/sum-swap-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int arraySum(int *array, int arraySize) {
        int s = 0;
        int *p = array;
        for (int i = 0; i < arraySize; i++) {
                s += *p;
                p++;
        }
        return s;
}
int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findSwapValues(int *array1, int array1Size, int *array2, int array2Size, int *returnSize) {
        *returnSize = 0;
        int s1 = arraySum(array1, array1Size), s2 = arraySum(array2, array2Size);
        if (((s1 - s2) & 1) == 1) {
                return NULL;
        }
        int d = (s1 - s2) >> 1;
        for (int i = 0; i < array1Size; i++) {
                array1[i] -= d;
        }

        qsort(array1, array1Size, sizeof(int), cmpfunc);
        qsort(array2, array2Size, sizeof(int), cmpfunc);

        for (int i = 0; i < array1Size; i++) {
                if (i > 0 && array1[i] == array1[i - 1]) {
                        continue;
                }
                // bin search
                int m, l = 0, r = array2Size - 1, target = array1[i];
                while (l < r) {
                        m = l + ((r - l) >> 1);
                        if (array2[m] >= target) {
                                r = m;
                        } else {
                                l = m + 1;
                        }
                }
                if (array2[r] == target) {
                        *returnSize = 2;
                        int *ans = (int *)calloc(2, sizeof(int));
                        ans[0] = target + d;
                        ans[1] = target;
                        return ans;
                }
        }
        return NULL;
}
int main() {
        int array1[] = {4, 1, 2, 1, 1, 2};
        int array2[] = {3, 6, 3, 3};

        int returnValue = 0;

        int *ans = findSwapValues(array1, 6, array2, 4, &returnValue);
        for (int i = 0; i < returnValue; i++) {
                printf("%d\n", ans[i]);
        }
        return 0;
}