/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-20
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一个正整数数组 grades ，表示大学中一些学生的成绩。
// 你打算将 所有 学生分为一些 有序 的非空分组，其中分组间的顺序满足以下全部条件：

// 第 i 个分组中的学生总成绩 小于 第 (i + 1) 个分组中的学生总成绩，对所有组均成立（除了最后一组）。
// 第 i 个分组中的学生总数 小于 第 (i + 1) 个分组中的学生总数，对所有组均成立（除了最后一组）。
// 返回可以形成的 最大 组数。

// 示例 1：

// 输入：grades = [10,6,12,7,3,5]
// 输出：3
// 解释：下面是形成 3 个分组的一种可行方法：
// - 第 1 个分组的学生成绩为 grades = [12] ，总成绩：12 ，学生数：1
// - 第 2 个分组的学生成绩为 grades = [6,7] ，总成绩：6 + 7 = 13 ，学生数：2
// - 第 3 个分组的学生成绩为 grades = [10,3,5] ，总成绩：10 + 3 + 5 = 18 ，学生数：3
// 可以证明无法形成超过 3 个分组。
// 示例 2：

// 输入：grades = [8,8]
// 输出：1
// 解释：只能形成 1 个分组，因为如果要形成 2 个分组的话，会导致每个分组中的学生数目相等。
//  

// 提示：

// 1 <= grades.length <= 105
// 1 <= grades[i] <= 105

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/maximum-number-of-groups-entering-a-competition
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int maximumGroups(int *grades, int gradesSize) {
        int cnt = 1, base = 1, n = gradesSize - 1;
        while (n > 0) {
                base++;
                n -= base;
                if (n >= 0)
                        cnt += 1;
        }
        return cnt;
}

int main() {
        int grades[] = {10, 6, 12, 7, 3, 5};
        printf("%d\n", maximumGroups(grades, 6));
        return 0;
}