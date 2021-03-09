/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-08
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
#include <string.h>

// 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。
// 返回 s 所有可能的分割方案。

// 回文串 是正着读和反着读都一样的字符串。

//  

// 示例 1：

// 输入：s = "aab"
// 输出：[["a","a","b"],["aa","b"]]
// 示例 2：

// 输入：s = "a"
// 输出：[["a"]]
//  

// 提示：

// 1 <= s.length <= 16
// s 仅由小写英文字母组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/palindrome-partitioning
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

void dfs(char *s, int l, int i, bool **dp, char ***ret, int *retSize, int *retColSize, char **ans,
         int *ansSize) {
        if (i == l) {
                char **tmp = malloc(sizeof(char *) * (*ansSize));
                for (int j = 0; j < (*ansSize); j++) {
                        int ansColSize = strlen(ans[j]);
                        tmp[j] = malloc(sizeof(char) * (ansColSize + 1));
                        strcpy(tmp[j], ans[j]);
                }
                ret[*retSize] = tmp;
                retColSize[*retSize] = (*ansSize);
                (*retSize)++;
                return;
        }

        for (int j = i; j < l; j++) {
                if (dp[i][j]) {
                        char *sub = malloc(sizeof(char) * (j - i + 2));
                        for (int k = i; k <= j; k++) {
                                sub[k - i] = s[k];
                        }
                        sub[j - i + 1] = '\0';
                        ans[(*ansSize)++] = sub;
                        dfs(s, l, j + 1, dp, ret, retSize, retColSize, ans, ansSize);
                        --(*ansSize);
                }
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***partition(char *s, int *returnSize, int **returnColumnSizes) {

        int l = strlen(s);
        int maxLen = l * (1 << l);
        char ***ret = (char ***)malloc(sizeof(char **) * maxLen);
        *returnSize = 0;
        *returnColumnSizes = (int *)malloc(sizeof(int) * maxLen);
        bool **dp = malloc(sizeof(bool *) * l); // dp[i][j] = s[i:j] is palindrome or not
        for (int i = 0; i < l; i++) {
                dp[i] = malloc(sizeof(bool) * l);
                for (int j = 0; j < l; j++) {
                        dp[i][j] = true;
                }
        }

        for (int i = l - 1; i >= 0; i--) {
                for (int j = i + 1; j < l; j++) {
                        dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
                }
        }

        char *ans[l];
        int ansSize = 0;

        dfs(s, l, 0, dp, ret, returnSize, *returnColumnSizes, ans, &ansSize);
        for (int i = 0; i < l; i++) {
                free(dp[i]);
        }
        free(dp);
        return ret;
}

int main() {
        char s[] = "abb";
        int returnSize;
        int *returnColSizes;

        char ***ans = partition(s, &returnSize, &returnColSizes);
        for (int i = 0; i < returnSize; i++) {
                for (int j = 0; j < returnColSizes[i]; j++) {
                        printf("%s ", ans[i][j]);
                        free(ans[i][j]);
                }
                free(ans[i]);
                puts("");
        }
        free(ans);
        free(returnColSizes);

        return 0;
}