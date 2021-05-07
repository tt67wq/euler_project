/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-30
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

// 一只青蛙想要过河。 假定河流被等分为若干个单元格，
// 并且在每一个单元格内都有可能放有一块石子（也有可能没有）
// 青蛙可以跳上石子，但是不可以跳入水中。

// 给你石子的位置列表 stones（用单元格序号 升序 表示）， 
// 请判定青蛙能否成功过河（即能否在最后一步跳至最后一块石子上）。

// 开始时， 青蛙默认已站在第一块石子上，
// 并可以假定它第一步只能跳跃一个单位（即只能从单元格 1 跳至单元格 2 ）。

// 如果青蛙上一步跳跃了 k 个单位，
// 那么它接下来的跳跃距离只能选择为 k - 1、k 或 k + 1
// 个单位。 另请注意，青蛙只能向前方（终点的方向）跳跃。

// 示例 1：

// 输入：stones = [0,1,3,5,6,8,12,17]
// 输出：true
// 解释：青蛙可以成功过河，按照如下方案跳跃：跳 1 个单位到第 2 块石子, 然后跳 2 个单位到第 3 块石子,
// 接着 跳 2 个单位到第 4 块石子, 然后跳 3 个单位到第 6 块石子, 跳 4 个单位到第 7 块石子, 最后，跳 5
// 个单位到第 8 个石子（即最后一块石子）。 示例 2：

// 输入：stones = [0,1,2,3,4,8,9,11]
// 输出：false
// 解释：这是因为第 5 和第 6 个石子之间的间距太大，没有可选的方案供青蛙跳跃过去。
//  

// 提示：

// 2 <= stones.length <= 2000
// 0 <= stones[i] <= 2^31 - 1
// stones[0] == 0

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/frog-jump
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct stone_index {
        int block;
        int index;
        UT_hash_handle hh;
};

bool canCross(int *stones, int stonesSize) {

        // dp[i][j] => can frog jump to stones[i] and jump j blocks last time

        bool **dp = (bool **)calloc(stonesSize, sizeof(bool *));
        for (int i = 0; i < stonesSize; i++) {
                dp[i] = (bool *)calloc(stonesSize + 1, sizeof(bool));
        }

        struct stone_index *table = NULL;
        for (int i = 0; i < stonesSize; i++) {
                struct stone_index *_stone =
                    (struct stone_index *)calloc(1, sizeof(struct stone_index));
                _stone->block = stones[i];
                _stone->index = i;
                HASH_ADD_INT(table, block, _stone);
        }

        dp[0][0] = true;

        for (int i = 0; i < stonesSize; i++) {
                int b = stones[i];
                for (int j = 0; j <= i; j++) {
                        int nb;
                        struct stone_index *_s;
                        if (dp[i][j]) {
                                // j
                                if (j > 0) {
                                        nb = b + j;
                                        HASH_FIND_INT(table, &nb, _s);
                                        if (_s != NULL) {
                                                dp[_s->index][j] = true;
                                        }
                                }

                                // j+1
                                nb = b + j + 1;
                                HASH_FIND_INT(table, &nb, _s);
                                if (_s != NULL) {
                                        dp[_s->index][j + 1] = true;
                                }

                                // j-1
                                if (j > 1) {
                                        nb = b + j - 1;
                                        HASH_FIND_INT(table, &nb, _s);
                                        if (_s != NULL) {
                                                dp[_s->index][j - 1] = true;
                                        }
                                }
                        }
                }
        }

        bool res = false;
        for (int j = 0; j < stonesSize + 1; j++) {
                if (dp[stonesSize - 1][j]) {
                        res = true;
                        break;
                }
        }
        // gc
        return res;
}

int main() {
        int stones[] = {0, 1, 2, 3, 4, 8, 9, 11};
        bool res = canCross(stones, sizeof(stones) / sizeof(stones[0]));
        printf("%d\n", res);
        return 0;
}