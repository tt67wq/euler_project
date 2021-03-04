/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-04
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。
// 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

// 请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。

// 说明:
// 不允许旋转信封。

// 示例:

// 输入: envelopes = [[5,4],[6,4],[6,7],[2,3]]
// 输出: 3
// 解释: 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/russian-doll-envelopes
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define DEBUG

int cmpfunc1(const void *a, const void *b) { return (*(int **)a)[0] - (*(int **)b)[0]; }
int cmpfunc2(const void *a, const void *b) { return (*(int **)b)[1] - (*(int **)a)[1]; }

int maxEnvelopes(int **envelopes, int envelopesSize, int *envelopesColSize) {
        qsort(envelopes, envelopesSize, sizeof(int **), cmpfunc2);
        qsort(envelopes, envelopesSize, sizeof(int **), cmpfunc1);

        int ans = 0;
        int *dp = (int *)calloc(sizeof(int), (envelopesSize + 1));

#ifdef DEBUG
        for (int i = 0; i < envelopesSize; i++) {
                printf("[%d, %d]\n", envelopes[i][0], envelopes[i][1]);
        }
#endif

        for (int i = 0; i < envelopesSize; i++) {
#ifdef DEBUG
                for (int j = 0; j <= envelopesSize; j++) {
                        printf("%d ", dp[j]);
                }
                puts("");
#endif

                int left = 0, right = ans;

                while (left < right) {
                        int mid = left + (right - left) / 2;
                        if (envelopes[i][1] > dp[mid]) {
                                left = mid + 1;
                        } else {
                                right = mid;
                        }
                }
                dp[left] = envelopes[i][1];
                if (left == ans) {
                        ans++;
                }
        }

        free(dp);
        return ans;
}

int main() {
        //[[4,5],[4,6],[6,7],[2,3],[1,1],[1,1]]
        int e0[] = {4, 5}, e1[] = {4, 6}, e2[] = {6, 7}, e3[] = {2, 3}, e4[] = {1, 1},
            e5[] = {1, 1};
        int *es[] = {e0, e1, e2, e3, e4, e5};

        int ans = maxEnvelopes(es, 6, NULL);
        printf("%d\n", ans);

        return 0;
}