/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一个整数数组 perm ，它是前 n 个正整数的排列，且 n 是个 奇数 。

// 它被加密成另一个长度为 n - 1 的整数数组 encoded ，满足 encoded[i] = perm[i] XOR perm[i + 1] 。
// 比方说，如果 perm = [1,3,2] ，那么 encoded = [2,1] 。

// 给你 encoded 数组，请你返回原始数组 perm 。题目保证答案存在且唯一。

//  

// 示例 1：

// 输入：encoded = [3,1]
// 输出：[1,2,3]
// 解释：如果 perm = [1,2,3] ，那么 encoded = [1 XOR 2,2 XOR 3] = [3,1]
// 示例 2：

// 输入：encoded = [6,5,4,6]
// 输出：[2,4,1,5,3]

// 3 <= n < 105
// n 是奇数。
// encoded.length == n - 1

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/decode-xored-permutation
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *decode(int *encoded, int encodedSize, int *returnSize) {
        int all = 0, odds = 0;
        for (int i = 1; i <= encodedSize + 1; i++) {
                all ^= i;
        }
        for (int i = 1; i < encodedSize; i += 2) {
                odds ^= encoded[i];
        }
        int *res = (int *)calloc(encodedSize + 1, sizeof(int));
        res[0] = all ^ odds;

        for (int i = 1; i < encodedSize + 1; i++) {
                res[i] = res[i - 1] ^ encoded[i - 1];
        }
        (*returnSize) = encodedSize + 1;
        return res;
}

int main() {
        int encoded[] = {6, 5, 4, 6};
        int returnSize;
        int *res = decode(encoded, sizeof(encoded) / sizeof(int), &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", res[i]);
        }
        return 0;
}