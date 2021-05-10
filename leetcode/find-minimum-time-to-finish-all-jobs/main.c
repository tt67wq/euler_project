/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-08
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

// 给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。
// 请你将这些工作分配给 k 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。
// 工人的 工作时间 是完成分配给他们的所有工作花费时间的总和。
// 请你设计一套最佳的工作分配方案，使工人的 最大工作时间 得以 最小化 。

// 返回分配方案中尽可能 最小 的 最大工作时间 。

//  

// 示例 1：

// 输入：jobs = [3,2,3], k = 3
// 输出：3
// 解释：给每位工人分配一项工作，最大工作时间是 3 。
// 示例 2：

// 输入：jobs = [1,2,4,7,8], k = 2
// 输出：11
// 解释：按下述方式分配工作：
// 1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
// 2 号工人：4、7（工作时间 = 4 + 7 = 11）
// 最大工作时间是 11 。
//  

// 提示：

// 1 <= k <= jobs.length <= 12
// 1 <= jobs[i] <= 107
// 通过次数9,510提交次数19,769

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

void backtrace(int *jobs, int jobsSize, int limit, int k, int idx, int *workloads, bool *res) {
        if (idx == jobsSize) {
                (*res) = true;
                return;
        }
        if (*res) {
                return;
        }

        int jb = jobs[idx];

        for (int i = 0; i < k; i++) {
                if (workloads[i] + jb <= limit) {
                        workloads[i] += jb;
                        backtrace(jobs, jobsSize, limit, k, idx + 1, workloads, res);
                        workloads[i] -= jb;
                }
                if (workloads[i] == 0) {
                        return;
                }
        }
}

int cmpfunc(const void *a, const void *b) {
        int fa = *(int *)a;
        int fb = *(int *)b;

        if (fa > fb) {
                return -1;
        } else if (fa < fb) {
                return 1;
        }
        return 0;
}

int minimumTimeRequired(int *jobs, int jobsSize, int k) {
        qsort(jobs, jobsSize, sizeof(int), cmpfunc);

        int left = 0, right = 0;
        for (int i = 0; i < jobsSize; i++) {
                right += jobs[i];
                left = left > jobs[i] ? left : jobs[i];
        }

        int *workloads = (int *)calloc(k, sizeof(int));
        while (left < right) {
                memset(workloads, 0, k * sizeof(int));
                int mid = (right + left) >> 1;
                bool pass = false;
                backtrace(jobs, jobsSize, mid, k, 0, workloads, &pass);
                if (pass) {
                        right = mid;
                } else {
                        left = mid + 1;
                }
        }
        return left;
}

int main() {
        int jobs[] = {3, 2, 3};
        int res = minimumTimeRequired(jobs, sizeof(jobs) / sizeof(int), 3);
        printf("%d\n", res);
        return 0;
}