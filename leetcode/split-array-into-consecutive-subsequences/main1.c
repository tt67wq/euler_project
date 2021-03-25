/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-25
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

// 给你一个按升序排序的整数数组 num（可能包含重复数字），
// 请你将它们分割成一个或多个长度至少为 3 的子序列，其中每个子序列都由连续整数组成。

// 如果可以完成上述分割，则返回 true ；否则，返回 false 。

//  

// 示例 1：

// 输入: [1,2,3,3,4,5]
// 输出: True
// 解释:
// 你可以分割出这样两个连续子序列 :
// 1, 2, 3
// 3, 4, 5
// 示例 2：

// 输入: [1,2,3,3,4,4,5,5]
// 输出: True
// 解释:
// 你可以分割出这样两个连续子序列 :
// 1, 2, 3, 4, 5
// 3, 4, 5
// 示例 3：

// 输入: [1,2,3,4,4,5]
// 输出: False
//  

// 提示：

// 1 <= nums.length <= 10000

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/split-array-into-consecutive-subsequences
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX 3500

struct node {
        int top;
        int cnt;
        bool enable;
};

void dfs(struct node *stacks, int *nums, int numsSize, int index, bool *ans) {
        if (*ans) {
                return;
        }
        if (index == numsSize) {
                for (int i = 0; i < MAX && stacks[i].enable; i++) {
                        if (stacks[i].cnt < 3) {
                                return;
                        }
                }
                (*ans) = true;
                return;
        }

        bool hit = false;
        int n = nums[index];
        for (int i = 0; i < MAX && stacks[i].enable; i++) {
                if (*ans) {
                        return;
                }
                if (stacks[i].top < n - 1 && stacks[i].cnt < 3) {
                        return;
                }
                if (stacks[i].top == n - 1) {
                        hit = true;
                        stacks[i].top = n;
                        stacks[i].cnt += 1;
                        dfs(stacks, nums, numsSize, index + 1, ans);
                        stacks[i].top = n - 1;
                        stacks[i].cnt -= 1;
                        if (stacks[i].cnt == 0) {
                                stacks[i].enable = false;
                        }
                }
        }
        // no enable entry
        if (!hit) {
                int j = 0;
                for (; j < MAX && stacks[j].enable; j++) {
                }
                stacks[j].enable = true;
                stacks[j].top = n;
                stacks[j].cnt = 1;
                dfs(stacks, nums, numsSize, index + 1, ans);
        }
}

bool isPossible(int *nums, int numsSize) {
        struct node *stacks = (struct node *)malloc(sizeof(struct node) * MAX);
        for (int i = 0; i < MAX; i++) {
                stacks[i].top = 0;
                stacks[i].cnt = 0;
                stacks[i].enable = false;
        }
        bool ans = false;
        dfs(stacks, nums, numsSize, 0, &ans);

        free(stacks);

        return ans;
}

int main() {
        int nums[] = {1, 2, 3, 3, 4, 5, 5, 5, 5, 6, 6, 7, 8, 9, 9, 9, 9, 10, 12, 13};
        bool ans = isPossible(nums, 20);
        printf("%d\n", ans);
        return 0;
}