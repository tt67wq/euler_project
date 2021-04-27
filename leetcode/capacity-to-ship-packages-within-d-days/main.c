/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-27
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。

// 传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。
// 我们装载的重量不会超过船的最大运载重量。

// 返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

//  

// 示例 1：

// 输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
// 输出：15
// 解释：
// 船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
// 第 1 天：1, 2, 3, 4, 5
// 第 2 天：6, 7
// 第 3 天：8
// 第 4 天：9
// 第 5 天：10

// 请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成
// (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的
// 示例 2：

// 输入：weights = [3,2,2,4,1,4], D = 3
// 输出：6
// 解释：
// 船舶最低载重 6 就能够在 3 天内送达所有包裹，如下所示：
// 第 1 天：3, 2
// 第 2 天：2, 4
// 第 3 天：1, 4
// 示例 3：

// 输入：weights = [1,2,3,1,1], D = 4
// 输出：3
// 解释：
// 第 1 天：1
// 第 2 天：2
// 第 3 天：3
// 第 4 天：1, 1
//  

// 提示：

// 1 <= D <= weights.length <= 50000
// 1 <= weights[i] <= 500

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

static bool greed(const int w, const int *weighs, const int weighsSize, const int D) {
        int i = 0, j = 0, acc = 0;
        while (i < D) {
                while (acc < w && j < weighsSize) {
                        acc += weighs[j++];
                }
                if (acc > w) {
                        j--;
                }
                if (j == weighsSize) {
                        return true;
                }
                acc = 0;
                i++;
        }
        return false;
}

int shipWithinDays(int *weights, int weightsSize, int D) {
        int max = INT32_MIN, s = 0;
        for (int i = 0; i < weightsSize; i++) {
                max = max > weights[i] ? max : weights[i];
                s += weights[i];
        }
        if (D == 1) {
                return s;
        }

        // bin search
        int l = max, r = s, m;
        while (l < r) {
                m = (l + r) >> 1;
                if (greed(m, weights, weightsSize, D)) {
                        r = m;
                } else {
                        l = m + 1;
                }
        }
        return l;
}

int main() {
        int weights[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int ans = shipWithinDays(weights, sizeof(weights) / sizeof(int), 5);
        printf("%d\n", ans);
        return 0;
}