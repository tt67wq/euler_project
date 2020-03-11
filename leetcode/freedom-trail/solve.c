/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-11
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int findRotateSteps(char *ring, char *key) {
        int rl = strlen(ring);
        int kl = strlen(key);
        // dp[i][j]表示已经完成了i个字符并且此时ring[j]指向12点 所需要转动的最小距离 ans =
        // min(dp[kl-1][:])
        int **dp = (int **)calloc(kl, sizeof(int *));
        for (int i = 0; i < kl; i++) {
                dp[i] = (int *)calloc(rl, sizeof(int));
        }

        /* int dp[kl][rl] = {0}; */

        // 记录ring上每个字符所在位置
        int arrs[26][20] = {0};
        int counters[26] = {0};
        for (int i = 0; i < rl; i++) {
                arrs[ring[i] - 'a'][counters[ring[i] - 'a']] = i;
                counters[ring[i] - 'a']++;
        }

        // 第一个字符
        for (int i = 0; i < counters[key[0] - 'a']; i++) {
                int pos = arrs[key[0] - 'a'][i];
                int min = pos < rl - pos ? pos : rl - pos; // 最小移动距离
                dp[0][pos] = min;
#if DEBUG
                printf("dp[0][%d] = %d\n", pos, dp[0][pos]);
#endif
        }

        // 剩余字符
        for (int i = 1; i < kl; i++) {
                for (int j = 0; j < counters[key[i] - 'a']; j++) {
                        int ori_pos = arrs[key[i] - 'a'][j]; // key[i]字符在ring中所在位置
                        dp[i][ori_pos] = INT_MAX;            // 设定最大值
                        for (int k = 0; k < counters[key[i - 1] - 'a']; k++) {
                                int cur_12 = arrs[key[i - 1] - 'a'][k]; // 12点指向的位置
                                int cur_pos = ori_pos >= cur_12
                                                  ? ori_pos - cur_12
                                                  : rl + ori_pos - cur_12; // key[i] 现在所在位置
                                int min =
                                    cur_pos < rl - cur_pos ? cur_pos : rl - cur_pos; // 最小移动距离

                                int min_acc = min + dp[i - 1][cur_12]; // 累计转动距离
                                dp[i][ori_pos] =
                                    min_acc < dp[i][ori_pos] ? min_acc : dp[i][ori_pos];
                        }
#if DEBUG
                        printf("dp[%d][%d] = %d\n", i, ori_pos, dp[i][ori_pos]);
#endif
                }
        }

        int ans = INT_MAX;

        // 最后一个字符
        for (int i = 0; i < counters[key[kl - 1] - 'a']; i++) {
                int pos = arrs[key[kl - 1] - 'a'][i];
                ans = dp[kl - 1][pos] < ans ? dp[kl - 1][pos] : ans;
        }

        return ans + kl;
}

int main() {
        printf("%d\n", findRotateSteps("ababcab", "acbaacba"));
        return 0;
}
