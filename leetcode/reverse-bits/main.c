/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-29
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 颠倒给定的 32 位无符号整数的二进制位。

// 进阶:
// 如果多次调用这个函数，你将如何优化你的算法？

// 示例 1：

// 输入: 00000010100101000001111010011100
// 输出: 00111001011110000010100101000000
// 解释: 输入的二进制串 00000010100101000001111010011100 表示无符号整数 43261596，
//      因此返回 964176192，其二进制表示形式为 00111001011110000010100101000000。
// 示例 2：

// 输入：11111111111111111111111111111101
// 输出：10111111111111111111111111111111
// 解释：输入的二进制串 11111111111111111111111111111101 表示无符号整数 4294967293，
//      因此返回 3221225471 其二进制表示形式为 10111111111111111111111111111111 。

// 提示：

// 输入是一个长度为 32 的二进制字符串

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/reverse-bits
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        int i = 0;
        while (n) {
                ans <<= 1;
                ans += (n & 1);
                n >>= 1;
                i++;
        }
        return i ? ans << (32 - i) : 0;
}

int main() {
        printf("%u\n", reverseBits(0));
        // printf("%u\n", reverseBits(43261596));
        // printf("%u\n", reverseBits(4294967293));

        return 0;
}