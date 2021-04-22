/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一个整数数组 arr 和两个整数 k 和 threshold 。

// 请你返回长度为 k 且平均值大于等于 threshold 的子数组数目。

//  

// 示例 1：

// 输入：arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
// 输出：3
// 解释：子数组 [2,5,5],[5,5,5] 和 [5,5,8] 的平均值分别为 4，5 和 6 。其他长度为 3
// 的子数组的平均值都小于 4 （threshold 的值)。 示例 2：

// 输入：arr = [1,1,1,1,1], k = 1, threshold = 0
// 输出：5
// 示例 3：

// 输入：arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
// 输出：6
// 解释：前 6 个长度为 3 的子数组平均值都大于 5 。注意平均值不是整数。
// 示例 4：

// 输入：arr = [7,7,7,7,7,7,7], k = 7, threshold = 7
// 输出：1
// 示例 5：

// 输入：arr = [4,4,4,4], k = 4, threshold = 1
// 输出：1

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))

int numOfSubarrays(int *arr, int arrSize, int k, int threshold) {
        int sum = 0;
        for (int i = 0; i < arrSize; i++) {
                sum += arr[i];
        }
        if (arrSize == k) {

                if (sum >= threshold * k) {
                        return 1;
                }
                return 0;
        }
        int ans = 0;
        int ts = 0;
        int left = 0, right = k;
        for (int i = 0; i < k; i++) {
                ts += arr[i];
        }

        do {
                if (threshold * k <= ts) {
                        ans += 1;
                }
                ts -= arr[left++];
                ts += arr[right++];
        } while (right < arrSize);

        if (threshold * k <= ts) {
                ans += 1;
        }
        return ans;
}

int main() {

        // int arr[] = {11, 13, 17, 23, 29, 31, 7, 5, 2, 3};
        int arr[] = {2, 2, 2, 2, 5, 5, 5, 8};
        printf("%d\n", numOfSubarrays(arr, ARRAY_SIZE(arr), 3, 4));
        return 0;
}