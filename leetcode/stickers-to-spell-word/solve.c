/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-12
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

// 背包法
int minStickers(char **stickers, int stickersSize, char *target) {
        int tl = strlen(target);
        int dp[1 << tl]; // dp[i]表示到达状态i需要的纸张

        memset(dp, -1, sizeof(int) * (1 << tl)); // 全未覆盖

        dp[0] = 0;
        for (int i = 0; i < stickersSize; i++) { // 遍历纸张
                char *sticker = stickers[i];
                for (int status = 0; status < (1 << tl); status++) { // 遍历覆盖的状态
                        if (dp[status] == -1) {
                                continue;
                        }
                        int curStatus = status;
                        for (int j = 0; j < strlen(sticker); j++) {
                                char c = sticker[j];
                                for (int k = 0; k < tl; k++) {
                                        if (c == target[k] && (curStatus & (1 << k)) == 0) {
                                                curStatus |= (1 << k); // 覆盖第k位
                                                break;
                                        }
                                }
                        }
                        // 讨论
                        int min = dp[curStatus] > dp[status] + 1 ? dp[status] + 1 : dp[curStatus];
                        dp[curStatus] = dp[curStatus] == -1 ? dp[status] + 1 : min;
                }
        }
        return dp[(1 << tl) - 1];
}

int main() {
        char *stickers[] = {"with", "example", "science"};
        printf("%d\n", minStickers(stickers, 3, "thehat"));
        return 0;
}
