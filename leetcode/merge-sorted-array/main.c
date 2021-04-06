/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

// 合并两个有序数组
// 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

// 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m +
// n，这样它就有足够的空间保存来自 nums2 的元素。

// 示例 1：

// 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// 输出：[1,2,2,3,5,6]
// 示例 2：

// 输入：nums1 = [1], m = 1, nums2 = [], n = 0
// 输出：[1]

// 提示：

// nums1.length == m + n
// nums2.length == n
// 0 <= m, n <= 200
// 1 <= m + n <= 200
// -109 <= nums1[i], nums2[i] <= 109

struct node {
        int val;
        SIMPLEQ_ENTRY(node) next;
};

SIMPLEQ_HEAD(head, node);

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n) {
        struct head *phead = (struct head *)malloc(sizeof(struct head));
        SIMPLEQ_INIT(phead);

        int p1 = 0, p2 = 0, k;
        while (p1 < m && p2 < n) {
                if (nums1[p1] < nums2[p2]) {
                        k = nums1[p1];
                        p1++;
                } else {
                        k = nums2[p2];
                        p2++;
                }
                struct node *tmp = (struct node *)malloc(sizeof(struct node));
                tmp->val = k;
                SIMPLEQ_INSERT_TAIL(phead, tmp, next);
        }
        if (p1 < m) {
                for (int i = p1; i < m; i++) {
                        struct node *tmp = (struct node *)malloc(sizeof(struct node));
                        tmp->val = nums1[i];
                        SIMPLEQ_INSERT_TAIL(phead, tmp, next);
                }
        }
        if (p2 < n) {
                for (int i = p2; i < n; i++) {
                        struct node *tmp = (struct node *)malloc(sizeof(struct node));
                        tmp->val = nums2[i];
                        SIMPLEQ_INSERT_TAIL(phead, tmp, next);
                }
        }

        int i = 0;
        while (!SIMPLEQ_EMPTY(phead)) {
                /* code */
                nums1[i++] = SIMPLEQ_FIRST(phead)->val;
                SIMPLEQ_REMOVE_HEAD(phead,next);
        }
}

int main() { return 0; }