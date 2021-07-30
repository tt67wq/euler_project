/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-07-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 逐行 依次按 “之” 字形进行标记。

// 如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；

// 而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记。

// 给你树上某一个节点的标号 label，请你返回从根节点到该标号为 label
// 节点的路径，该路径是由途经的节点标号所组成的。

//  

// 示例 1：

// 输入：label = 14
// 输出：[1,3,4,14]
// 示例 2：

// 输入：label = 26
// 输出：[1,2,6,10,26]
//  

// 提示：

// 1 <= label <= 10^6

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/path-in-zigzag-labelled-binary-tree
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define DEBUG

int cmpfunc(const void *a, const void *b) {
        int _a = *(int *)a;
        int _b = *(int *)b;

        return _a > _b ? 1 : -1;
}

int *pathInZigZagTree(int label, int *returnSize) {
        int *ans = (int *)calloc(20, sizeof(int));
        int *ansp = ans;

        *returnSize = 1;

        while (label > 1) {
                *ansp = label;
                ansp++;
                (*returnSize)++;
#ifdef DEBUG
                printf("%d\n", label);
#endif

                int i = 1;
                int _label = label;

                while (i <= _label) {
                        label ^= i;
                        i <<= 1;
                }
                i >>= 1;
                label += i;
                label >>= 1;
        }
        *ansp = 1;

        qsort(ans, *returnSize, sizeof(int), cmpfunc);
        return ans;
}

int main() {
        int returnSize;
        int *ans = pathInZigZagTree(16, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        puts("");
        return 0;
}