/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
// 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

// 示例 1：

// 输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
// 示例 2：

// 输入：nums = [0]
// 输出：[[],[0]]
//  

// 提示：

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/subsets-ii
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX 10

typedef struct _entry {
        int size;
        int *elems;
} entry;

struct node {
        entry *en;
        SLIST_ENTRY(node) ptr;
};

SLIST_HEAD(head, node);

int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}

void dfs(int *nums, int numsSize, int index, struct head *hp, int *returnSize) {
        if (index == numsSize) {
                struct node *ne = (struct node *)malloc(sizeof(struct node));
                ne->en = (entry *)malloc(sizeof(entry));
                ne->en->elems = (int *)malloc(sizeof(int) * MAX);
                ne->en->size = 0;
                SLIST_INSERT_HEAD(hp, ne, ptr);
                (*returnSize)++;
                return;
        }
        int num = nums[index];
        int i = index, cnt = 0;
        while (i < numsSize && nums[i] == num) {
                i++;
                cnt++;
        }
        dfs(nums, numsSize, i, hp, returnSize);

        struct node *np;
        SLIST_FOREACH(np, hp, ptr) {
                entry *m = np->en;
                for (int j = 1; j <= cnt; j++) {
                        struct node *ne = (struct node *)malloc(sizeof(struct node));
                        ne->en = (entry *)malloc(sizeof(entry));
                        ne->en->elems = (int *)malloc(sizeof(int) * MAX);
                        ne->en->size = m->size + j;
                        memcpy(ne->en->elems, m->elems, sizeof(int) * m->size);
                        for (int k = 0; k < j; k++) {
                                ne->en->elems[m->size + k] = num;
                        }

                        SLIST_INSERT_HEAD(hp, ne, ptr);
                        (*returnSize)++;
                }
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
        struct head *hp = (struct head *)malloc(sizeof(struct head));
        SLIST_INIT(hp);
        (*returnSize) = 0;

        qsort(nums, numsSize, sizeof(int), cmpfunc);
        dfs(nums, numsSize, 0, hp, returnSize);

        int **ans = (int **)malloc(sizeof(int *) * (*returnSize));
        *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));

        struct node *np;
        int i = 0;
        SLIST_FOREACH(np, hp, ptr) {
                // printf("[");
                // for (int i = 0; i < np->en->size; i++) {
                //         printf("%d ", np->en->elems[i]);
                // }
                // puts("]");
                ans[i] = (int *)malloc(sizeof(int) * np->en->size);
                memcpy(ans[i], np->en->elems, sizeof(int) * np->en->size);
                (*returnColumnSizes)[i++] = np->en->size;
        }
        return ans;
}

int main() {
        int nums[] = {1, 2, 2};
        int returnSize;
        int *returnColSize;
        subsetsWithDup(nums, 3, &returnSize, &returnColSize);
        return 0;
}