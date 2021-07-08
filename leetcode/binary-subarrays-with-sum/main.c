/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-07-08
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

// 给你一个二元数组 nums ，和一个整数 goal ，请你统计并返回有多少个和为 goal 的 非空 子数组。

// 子数组 是数组的一段连续部分。

//  

// 示例 1：

// 输入：nums = [1,0,1,0,1], goal = 2
// 输出：4
// 解释：
// 有 4 个满足题目要求的子数组：[1,0,1]、[1,0,1,0]、[0,1,0,1]、[1,0,1]
// 示例 2：

// 输入：nums = [0,0,0,0,0], goal = 0
// 输出：15
//  

// 提示：

// 1 <= nums.length <= 3 * 104
// nums[i] 不是 0 就是 1
// 0 <= goal <= nums.length

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/binary-subarrays-with-sum
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct numTable {
        int num;
        int cnt;
        UT_hash_handle hh;
};

int numSubarraysWithSum(int *nums, int numsSize, int goal) {

        struct numTable *tb = NULL;
        int *prefixSum = (int *)calloc(numsSize + 1, sizeof(int));
        struct numTable *init = (struct numTable *)malloc(sizeof(struct numTable));
        init->num = 0;
        init->cnt = 1;
        HASH_ADD_INT(tb, num, init);
        for (int i = 0; i < numsSize; i++) {
                prefixSum[i + 1] = prefixSum[i] + nums[i];
                struct numTable *en = NULL;
                HASH_FIND_INT(tb, &(prefixSum[i + 1]), en);
                if (en != NULL) {
                        en->cnt++;
                } else {
                        en = (struct numTable *)malloc(sizeof(struct numTable));
                        en->num = prefixSum[i + 1];
                        en->cnt = 1;
                        HASH_ADD_INT(tb, num, en);
                }
        }

        int ans = 0;
        struct numTable *iter, *tmp;
        HASH_ITER(hh, tb, iter, tmp) {
                printf("%d => %d\n", iter->num, iter->cnt);
                if (iter->num >= goal) {
                        struct numTable *s;
                        int diff = iter->num - goal;
                        HASH_FIND_INT(tb, &diff, s);
                        if (s != NULL) {
                                ans +=
                                    (goal ? iter->cnt * s->cnt : (iter->cnt * (s->cnt - 1)) >> 1);
                        }
                }
        }
        return ans;
}

int main() {
        int nums[] = {0, 0, 0, 0, 0};
        int ans = numSubarraysWithSum(nums, 5, 0);
        printf("%d\n", ans);
        return 0;
}