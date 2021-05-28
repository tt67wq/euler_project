/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-28
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

// 返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。

// 如果没有和至少为 K 的非空子数组，返回 -1 。

//  

// 示例 1：

// 输入：A = [1], K = 1
// 输出：1
// 示例 2：

// 输入：A = [1,2], K = 4
// 输出：-1
// 示例 3：

// 输入：A = [2,-1,2], K = 3
// 输出：3

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct elem {
        long p;
        TAILQ_ENTRY(elem) next;
};

TAILQ_HEAD(qhead, elem);

int shortestSubarray(int *nums, int numsSize, int k) {

        long *prefixSum = (long *)calloc(numsSize + 1, sizeof(long));
        // prefixSum[i] = sum(nums[0..i-1])
        for (int i = 0; i < numsSize; i++) {
                prefixSum[i + 1] = prefixSum[i] + (long)nums[i];
        }

        long ans = numsSize + 1;
        struct qhead *tq = (struct qhead *)malloc(sizeof(struct qhead));
        TAILQ_INIT(tq);

        for (int y = 0; y < numsSize + 1; y++) {
                while (!TAILQ_EMPTY(tq) && prefixSum[y] <= prefixSum[TAILQ_LAST(tq, qhead)->p]) {
                        struct elem *tmp = TAILQ_LAST(tq, qhead);
                        TAILQ_REMOVE(tq, tmp, next);
                }
                while (!TAILQ_EMPTY(tq) && prefixSum[y] >= prefixSum[TAILQ_FIRST(tq)->p] + k) {
                        struct elem *tmp = TAILQ_FIRST(tq);
                        TAILQ_REMOVE(tq, tmp, next);
                        long _d = (long)y - tmp->p;
                        ans = ans < _d ? ans : _d;
                }
                struct elem *tmp = (struct elem *)malloc(sizeof(struct elem));
                tmp->p = (long)y;
                TAILQ_INSERT_TAIL(tq, tmp, next);
        }

        return (int)(ans < numsSize + 1 ? ans : -1);
}

int main() {

        int nums[] = {1};

        int ans = shortestSubarray(nums, sizeof(nums) / sizeof(int), 1);
        printf("%d\n", ans);

        return 0;
}