/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-23
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

// 给定一个数字字符串 S，比如 S = "123456579"，
// 我们可以将它分成斐波那契式的序列 [123, 456, 579]。

// 形式上，斐波那契式序列是一个非负整数列表 F，且满足：

// 0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
// F.length >= 3；
// 对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
// 另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。

// 返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。

//  

// 示例 1：

// 输入："123456579"
// 输出：[123,456,579]
// 示例 2：

// 输入: "11235813"
// 输出: [1,1,2,3,5,8,13]
// 示例 3：

// 输入: "112358130"
// 输出: []
// 解释: 这项任务无法完成。
// 示例 4：

// 输入："0123"
// 输出：[]
// 解释：每个块的数字不能以零开头，因此 "01"，"2"，"3" 不是有效答案。
// 示例 5：

// 输入: "1101111"
// 输出: [110, 1, 111]
// 解释: 输出 [11,0,11,11] 也同样被接受。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/split-array-into-fibonacci-sequence
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNum(char *s, int len) {
        int64_t num = 0;

        for (int i = 0; i < len; i++) {
                num = num * 10 + s[i] - '0';
                if (num > INT32_MAX) {
                        return -1;
                }
        }
        return (int)num;
}

bool helper(char *s, int sid, int num0, int num1, int *ret, int *rsize) {
        if ((int64_t)num0 + num1 > INT32_MAX) {
                return false;
        }

        int slen = strlen(s);

        for (int i = sid; i < slen; i++) {
                int num2 = getNum(&s[sid], i - sid + 1);
                if (num2 == -1) {
                        break;
                }
                if (num2 == num0 + num1) {
                        ret[(*rsize)++] = num2;

                        if (i == slen - 1) {
                                return true;
                        }
                        bool tmp = helper(s, i + 1, num1, num2, ret, rsize);
                        if (tmp) {
                                return true;
                        }
                        (*rsize)--;
                } else if (num2 == 0 || num2 > num0 + num1) {
                        break;
                }
        }
        return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *splitIntoFibonacci(char *S, int *returnSize) {
        if (S == NULL || strlen(S) < 3) {
                *returnSize = 0;
                return NULL;
        }

        int slen = strlen(S), rsize = 0;
        size_t _size = sizeof(int) * slen;

        int *ret = malloc(_size);
        memset(ret, 0, _size);

        for (int i = 0; i < slen - 2; i++) {
                int num0 = getNum(S, i + 1);
                if (num0 == -1) {
                        break;
                }
                ret[0] = num0;

                for (int j = i + 1; j < slen - 1; j++) {
                        int num1 = getNum(&S[i + 1], j - i);
                        if (num1 == -1) {
                                break;
                        }
                        ret[1] = num1;
                        rsize = 2;

                        bool tmp = helper(S, j + 1, num0, num1, ret, &rsize);
                        if (tmp == true) {
                                goto DONE;
                        }
                        if (num1 == 0) {
                                break;
                        }
                }
                if (num0 == 0) {
                        break;
                }
        }
        *returnSize = 0;
        return NULL;
DONE:
        *returnSize = rsize;
        return ret;
}

int main() {
        char *S = "11235813";
        int returnSize;
        int *ans = splitIntoFibonacci(S, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        puts("");
        free(ans);
        return 0;
}