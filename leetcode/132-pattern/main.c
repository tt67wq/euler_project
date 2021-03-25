/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-24
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

// 给你一个整数数组 nums ，数组中共有 n 个整数。
// 132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，
// 并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。

// 如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。

// 进阶：很容易想到时间复杂度为 O(n^2) 的解决方案，
// 你可以设计一个时间复杂度为 O(n logn) 或 O(n) 的解决方案吗？

// 示例 1：

// 输入：nums = [1,2,3,4]
// 输出：false
// 解释：序列中不存在 132 模式的子序列。
// 示例 2：

// 输入：nums = [3,1,4,2]
// 输出：true
// 解释：序列中有 1 个 132 模式的子序列： [1, 4, 2] 。
// 示例 3：

// 输入：nums = [-1,3,2,0]
// 输出：true
// 解释：序列中有 3 个 132 模式的的子序列：[-1, 3, 2]、[-1, 3, 0] 和 [-1, 2, 0] 。
//  

// 提示：

// n == nums.length
// 1 <= n <= 104
// -109 <= nums[i] <= 109

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/132-pattern
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct node {
        int val;
        SLIST_ENTRY(node) ptr;
};

SLIST_HEAD(head, node);

struct head *lhead = NULL;

bool find132pattern(int *nums, int numsSize) {
        bool ans = false;
        struct node *top;
        lhead = (struct head *)malloc(sizeof(struct head));
        SLIST_INIT(lhead);

        int med = INT32_MIN;
        for (int i = numsSize - 1; i >= 0; i--) {
                if (nums[i] < med) {
                        ans = true;
                        break;
                }
                while (!SLIST_EMPTY(lhead) && SLIST_FIRST(lhead)->val < nums[i]) {
                        /* code */
                        top = SLIST_FIRST(lhead);
                        med = top->val;
                        SLIST_REMOVE_HEAD(lhead, ptr);
                        free(top);
                }
                struct node *tmp = (struct node *)malloc(sizeof(struct node));
                tmp->val = nums[i];
                SLIST_INSERT_HEAD(lhead, tmp, ptr);
        }
        while (!SLIST_EMPTY(lhead)) {
                top = SLIST_FIRST(lhead);
                SLIST_REMOVE_HEAD(lhead, ptr);
                free(top);
        }

        return ans;
}

int main() {
        int nums[] = {3, 1, 4, 2};
        bool ans = find132pattern(nums, 4);
        printf("%d\n", ans);
        return 0;
}