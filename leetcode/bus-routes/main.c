/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <uthash.h>

// 给你一个数组 routes ，表示一系列公交线路，其中每个 routes[i] 表示一条公交线路，第 i
// 辆公交车将会在上面循环行驶。

// 例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 ->
// ... 这样的车站路线行驶。 现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。
// 期间仅可乘坐公交车。

// 求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 -1 。

//  

// 示例 1：

// 输入：routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// 输出：2
// 解释：最优策略是先乘坐第一辆公交车到达车站 7 , 然后换乘第二辆公交车到车站 6 。
// 示例 2：

// 输入：routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
// 输出：-1
//  

// 提示：

// 1 <= routes.length <= 500.
// 1 <= routes[i].length <= 105
// routes[i] 中的所有值 互不相同
// sum(routes[i].length) <= 105
// 0 <= routes[i][j] < 106
// 0 <= source, target < 106

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/bus-routes
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX 100

struct stat_bus {
        int stat;
        int bus[MAX];
        int busSize;
        UT_hash_handle hh;
};

struct bus_visit {
        int bus;
        UT_hash_handle hh;
};

struct node {
        int bus;
        int stat;
        int step;
        SIMPLEQ_ENTRY(node) next;
};

SIMPLEQ_HEAD(qhead, node);

int numBusesToDestination(int **routes, int routesSize, int *routesColSize, int source,
                          int target) {

        // build next station map
        struct stat_bus *next_map = NULL;

        for (int i = 0; i < routesSize; i++) {
                for (int j = 0; j < routesColSize[i]; j++) {
                        int stat = routes[i][j];

                        struct stat_bus *buses;
                        HASH_FIND_INT(next_map, &stat, buses);

                        if (buses != NULL) {
                                buses->bus[buses->busSize++] = i;
                        } else {
                                buses = (struct stat_bus *)malloc(sizeof(struct stat_bus));
                                buses->stat = stat;
                                buses->busSize = 0;
                                buses->bus[buses->busSize++] = i;

                                HASH_ADD_INT(next_map, stat, buses);
                        }
                }
        }

        // bfs
        struct qhead *q = (struct qhead *)malloc(sizeof(struct qhead));
        SIMPLEQ_INIT(q);

        struct stat_bus *buses = NULL;
        HASH_FIND_INT(next_map, &(source), buses);
        if (buses == NULL) {
                return -1;
        }
        if (source == target) {
                return 0;
        }

        struct bus_visit *vis = NULL;
        for (int i = 0; i < buses->busSize; i++) {
                struct node *n = (struct node *)malloc(sizeof(struct node));
                n->bus = buses->bus[i];
                n->step = 1;
                n->stat = source;
                SIMPLEQ_INSERT_HEAD(q, n, next);

                struct bus_visit *vis_n = (struct bus_visit *)malloc(sizeof(struct bus_visit));
                vis_n->bus = buses->bus[i];
                HASH_ADD_INT(vis, bus, vis_n);
        }

        while (!SIMPLEQ_EMPTY(q)) {
                struct node *_top = SIMPLEQ_FIRST(q);
                SIMPLEQ_REMOVE_HEAD(q, next);

                int index = _top->bus;
                // printf("bus => %d, step => %d\n", index, _top->step);
                for (int i = 0; i < routesColSize[index]; i++) {
                        int stat = routes[index][i];
                        if (stat == target) {
                                return _top->step;
                        }
                        if (stat == _top->stat) {
                                continue;
                        }
                        struct stat_bus *buses = NULL;
                        HASH_FIND_INT(next_map, &(stat), buses);
                        for (int i = 0; i < buses->busSize; i++) {
                                if (buses->bus[i] == index) {
                                        continue;
                                }

                                struct bus_visit *vis_n;
                                HASH_FIND_INT(vis, &(buses->bus[i]), vis_n);
                                if (vis_n != NULL) {
                                        continue;
                                }

                                // printf("%d ", buses->bus[i]);

                                struct node *n = (struct node *)malloc(sizeof(struct node));
                                n->bus = buses->bus[i];
                                n->step = _top->step + 1;
                                n->stat = stat;
                                SIMPLEQ_INSERT_TAIL(q, n, next);

                                vis_n = (struct bus_visit *)malloc(sizeof(struct bus_visit));
                                vis_n->bus = buses->bus[i];
                                HASH_ADD_INT(vis, bus, vis_n);
                        }
                        // puts("");
                }
        }

        return -1;
}

int main() {
        int route0[] = {1, 2, 7};
        int route1[] = {3, 6, 7};

        int *routes[] = {route0, route1};
        int routeColSize[] = {sizeof(route0) / sizeof(int), sizeof(route1) / sizeof(int)};

        int ans = numBusesToDestination(routes, 2, routeColSize, 6, 6);
        printf("%d\n", ans);
        return 0;
}