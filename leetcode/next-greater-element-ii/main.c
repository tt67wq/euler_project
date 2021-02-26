/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-26
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

/* 给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），
输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，
这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。
如果不存在，则输出 -1。 */

/* 示例 1: */

/* 输入: [1,2,1] */
/* 输出: [2,-1,2] */
/* 解释: 第一个 1 的下一个更大的数是 2； */
/* 数字 2 找不到下一个更大的数；  */
/* 第二个 1 的下一个最大的数需要循环搜索，结果也是 2。 */
/* 注意: 输入数组的长度不会超过 10000。 */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/next-greater-element-ii */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#define DEBUG

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *nextGreaterElements(int *nums, int numsSize, int *returnSize) {
        if (numsSize == 0) {
                (*returnSize) = numsSize;
                return NULL;
        }
        int n = 2 * numsSize, top = 0;
        int *res = malloc(sizeof(int) * n);
        int stack[n];

        for (int i = n - 1; i >= 0; i--) {
                while (top > 0 && stack[top - 1] <= nums[i % numsSize]) {
                        top--;
                }
                res[i] = (top == 0) ? -1 : stack[top - 1];
                stack[top++] = nums[i % numsSize];
        }

        (*returnSize) = numsSize;
        return res;
}

int main() {
        int nums[] = {5, 4, 3, 2, 1};
        int returnSize;
        int *ans = nextGreaterElements(nums, 5, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        free(ans);
        puts("");
        return 1;
}
