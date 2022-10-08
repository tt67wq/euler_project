/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-08
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定两个大小相等的数组 nums1 和 nums2，nums1 相对于 nums2 的优势可以用满足 nums1[i] >
// nums2[i] 的索引 i 的数目来描述。

// 返回 nums1 的任意排列，使其相对于 nums2 的优势最大化。

//  

// 示例 1：

// 输入：nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// 输出：[2,11,7,15]
// 示例 2：

// 输入：nums1 = [12,24,8,32], nums2 = [13,25,32,11]
// 输出：[24,32,8,12]
//  

// 提示：

// 1 <= nums1.length <= 105
// nums2.length == nums1.length
// 0 <= nums1[i], nums2[i] <= 109

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/advantage-shuffle
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

typedef struct item {
        int idx;
        int val;
} item;

int cmpfunc1(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int cmpfunc2(const void *a, const void *b) { return ((item *)a)->val - ((item *)b)->val; }
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *advantageCount(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize) {
        int *ans = (int *)malloc(sizeof(int) * nums1Size);
        qsort(nums1, nums1Size, sizeof(int), cmpfunc1);

        item *nums2WithIndex = (item *)malloc(sizeof(item) * nums2Size);
        for (int i = 0; i < nums2Size; i++) {
                nums2WithIndex[i].idx = i;
                nums2WithIndex[i].val = nums2[i];
        }
        qsort(nums2WithIndex, nums2Size, sizeof(item), cmpfunc2);

        int left = 0, right = nums1Size - 1;
        for (int i = 0; i < nums1Size; i++) {
                if (nums1[i] > nums2[nums2WithIndex[left].idx]) {
                        ans[nums2WithIndex[left].idx] = nums1[i];
                        left++;
                } else {
                        ans[nums2WithIndex[right].idx] = nums1[i];
                        right--;
                }
        }
        free(nums2WithIndex);
        *returnSize = nums1Size;

        return ans;
}

int main() {
        int nums1[] = {2, 7, 11, 15};
        int nums2[] = {1, 10, 4, 11};
        int returnCount;

        advantageCount(nums1, 4, nums2, 4, &returnCount);
        return 0;
}