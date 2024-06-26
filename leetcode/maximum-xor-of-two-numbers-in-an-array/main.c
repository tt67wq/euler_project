/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-17
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
#include <uthash.h>

// 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。

// 进阶：你可以在 O(n) 的时间解决这个问题吗？

//  

// 示例 1：

// 输入：nums = [3,10,5,25,2,8]
// 输出：28
// 解释：最大运算结果是 5 XOR 25 = 28.
// 示例 2：

// 输入：nums = [0]
// 输出：0
// 示例 3：

// 输入：nums = [2,4]
// 输出：6
// 示例 4：

// 输入：nums = [8,10,2]
// 输出：10
// 示例 5：

// 输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
// 输出：127
//  

// 提示：

// 1 <= nums.length <= 2 * 104
// 0 <= nums[i] <= 231 - 1

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define HIGH_BIT 30

struct HashTable {
        int key;
        UT_hash_handle hh;
};

int findMaximumXOR(int *nums, int numsSize) {
        int x = 0;
        for (int k = HIGH_BIT; k >= 0; k--) {
                struct HashTable *preTable = NULL;
                for (int i = 0; i < numsSize; i++) {
                        int m = nums[i] >> k;
                        struct HashTable *tmp;
                        HASH_FIND_INT(preTable, &m, tmp);
                        if (tmp == NULL) {
                                tmp = (struct HashTable *)malloc(sizeof(struct HashTable));
                                tmp->key = m;
                                HASH_ADD_INT(preTable, key, tmp);
                        }
                }
                int _x = (x << 1) + 1;
                bool found = false;

                for (int i = 0; i < numsSize; i++) {
                        int m = _x ^ (nums[i] >> k);
                        struct HashTable *tmp;
                        HASH_FIND_INT(preTable, &m, tmp);
                        if (tmp != NULL) {
                                found = true;
                                break;
                        }
                }

                if (found) {
                        x = _x;
                } else {
                        x = _x - 1;
                }
        }
        return x;
}

int main() {
        int nums[] = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
        int ans = findMaximumXOR(nums, sizeof(nums) / sizeof(int));
        printf("%d\n", ans);
        return 0;
}