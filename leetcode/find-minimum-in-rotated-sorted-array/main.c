/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-08
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组
// nums = [0,1,2,4,5,6,7] 在变化后可能得到： 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2] 若旋转 7
// 次，则可以得到 [0,1,2,4,5,6,7] 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组
// [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

// 给你一个元素值 互不相同 的数组 nums
// ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

//  

// 示例 1：

// 输入：nums = [3,4,5,1,2]
// 输出：1
// 解释：原数组为 [1,2,3,4,5] ，旋转 3 次得到输入数组。
// 示例 2：

// 输入：nums = [4,5,6,7,0,1,2]
// 输出：0
// 解释：原数组为 [0,1,2,4,5,6,7] ，旋转 4 次得到输入数组。
// 示例 3：

// 输入：nums = [11,13,15,17]
// 输出：11
// 解释：原数组为 [11,13,15,17] ，旋转 4 次得到输入数组。
//  

// 提示：

// n == nums.length
// 1 <= n <= 5000
// -5000 <= nums[i] <= 5000
// nums 中的所有整数 互不相同
// nums 原来是一个升序排序的数组，并进行了 1 至 n 次旋转

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int findMin(int *nums, int numsSize) {
        if (nums[0] < nums[numsSize - 1]) {
                return nums[0];
        }

        // bin search
        int m, l = 0, r = numsSize - 1;
        while (l < r) {
                m = l + ((r - l) >> 1);
                if (nums[m] >= nums[0]) {
                        l = m + 1;
                } else {
                        r = m;
                }
        }
        return nums[l];
}

int main() {
        // int nums[] = {2, 1};
        // printf("%d\n", findMin(nums, 2));
        int nums[] = {4, 5, 6, 7, 0, 1, 2};
        printf("%d\n", findMin(nums, 7));
        return 0;
}