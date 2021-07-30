/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-08-02
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

// 有 n 个网络节点，标记为 1 到 n。

// 给你一个列表 times，表示信号经过 有向 边的传递时间。
// times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点，
// wi 是一个信号从源节点传递到目标节点的时间。

// 现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1
// 。

//  

// 示例 1：

// 输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// 输出：2
// 示例 2：

// 输入：times = [[1,2,1]], n = 2, k = 1
// 输出：1
// 示例 3：

// 输入：times = [[1,2,1]], n = 2, k = 2
// 输出：-1
//  

// 提示：

// 1 <= k <= n <= 100
// 1 <= times.length <= 6000
// times[i].length == 3
// 1 <= ui, vi <= n
// ui != vi
// 0 <= wi <= 100
// 所有 (ui, vi) 对都 互不相同（即，不含重复边）

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/network-delay-time
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int networkDelayTime(int **times, int timesSize, int *timesColSize, int n, int k) {

        int **g = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
                g[i] = (int *)malloc(n * sizeof(int));
                memset(g[i], 0x3f, sizeof(int) * n);
        }

        // init
        for (int i = 0; i < timesSize; i++) {
                int _f = times[i][0] - 1;
                int _t = times[i][1] - 1;
                g[_f][_t] = times[i][2];
        }

        int *dist = (int *)malloc(n * sizeof(int));
        memset(dist, 0x3f, n * sizeof(int));
        char *used = (char *)malloc(n * sizeof(char));
        memset(used, 0, n * sizeof(char));

        dist[k - 1] = 0;

        for (int i = 0; i < n; i++) {
                int x = -1;

                // 距离最小的点
                for (int y = 0; y < n; y++) {
                        if (!used[y] && (x == -1 || dist[y] < dist[x])) {
                                x = y;
                        }
                }

                // 用该点更新所有其他点的距离
                used[x] = 1;
                for (int y = 0; y < n; y++) {
                        dist[y] = MIN(dist[y], dist[x] + g[x][y]);
                }
        }

        // int ans = *max_element(dist.begin(), dist.end());
        // return ans == inf ? -1 : ans;
        int ans = -1;
        for (int i = 0; i < n; i++) {
                ans = MAX(ans, dist[i]);
        }

        return ans == 0x3f3f3f3f ? -1 : ans;
}

int main() {
        // [[2,1,1],[2,3,1],[3,4,1]]
        // 4
        // 2
        int t0[] = {2, 1, 1};
        int t1[] = {2, 3, 1};
        int t2[] = {3, 4, 1};

        int *times[] = {t0, t1, t2};
        int ans = networkDelayTime(times, 3, NULL, 4, 2);
        printf("%d\n", ans);

        return 0;
}