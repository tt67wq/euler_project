/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

// 如果数组是单调递增或单调递减的，那么它是单调的。

// 如果对于所有 i <= j，A[i] <= A[j]，那么数组 A 是单调递增的。 如果对于所有 i <= j，A[i]> =
// A[j]，那么数组 A 是单调递减的。

// 当给定的数组 A 是单调数组时返回 true，否则返回 false。

//  

// 示例 1：

// 输入：[1,2,2,3]
// 输出：true
// 示例 2：

// 输入：[6,5,4,4]
// 输出：true
// 示例 3：

// 输入：[1,3,2]
// 输出：false
// 示例 4：

// 输入：[1,2,4,5]
// 输出：true
// 示例 5：

// 输入：[1,1,1]
// 输出：true
//  

// 提示：

// 1 <= A.length <= 50000
// -100000 <= A[i] <= 100000

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/monotonic-array
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UP 1
#define DOWN 2
#define EQUAL 3

bool isMonotonic(int *A, int ASize) {
        if (ASize <= 1) {
                return true;
        }
        int direction = EQUAL;

        for (int i = 1; i < ASize; i++) {
                int tmp;
                if (A[i] > A[i - 1]) {
                        tmp = UP;
                } else if (A[i] < A[i - 1]) {
                        tmp = DOWN;
                } else {
                        tmp = EQUAL;
                }

                if (tmp != EQUAL) {
                        if (direction == EQUAL) {
                                direction = tmp;
                        } else {
                                if (direction == tmp) {
                                        ;
                                } else {
                                        return false;
                                }
                        }
                } else {
                        ;
                }
        }
        return true;
}

int main() {
        int A[] = {6, 5, 4, 4};
        printf("%d\n", isMonotonic(A, 4));
        return 0;
}