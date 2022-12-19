/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-12-19
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

// 有一个具有 n 个顶点的 双向 图，其中每个顶点标记从 0 到 n - 1（包含 0 和 n -
// 1）。图中的边用一个二维整数数组 edges 表示，其中 edges[i] = [ui, vi] 表示顶点 ui 和顶点 vi
// 之间的双向边。 每个顶点对由 最多一条 边连接，并且没有顶点存在与自身相连的边。

// 请你确定是否存在从顶点 source 开始，到顶点 destination 结束的 有效路径 。

// 给你数组 edges 和整数 n、source 和 destination，如果从 source 到 destination 存在 有效路径
// ，则返回 true，否则返回 false 。

// 示例 1：

// 输入：n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
// 输出：true
// 解释：存在由顶点 0 到顶点 2 的路径:
// - 0 → 1 → 2
// - 0 → 2
// 示例 2：

// 输入：n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
// 输出：false
// 解释：不存在由顶点 0 到顶点 5 的路径.

// 提示：

// 1 <= n <= 2 * 105
// 0 <= edges.length <= 2 * 105
// edges[i].length == 2
// 0 <= ui, vi <= n - 1
// ui != vi
// 0 <= source, destination <= n - 1
// 不存在重复边

typedef struct {
        int *parent;
        int *rank;
} DisjointSet;

DisjointSet *create(int n) {
        DisjointSet *obj = (DisjointSet *)malloc(sizeof(DisjointSet));
        obj->parent = (int *)calloc(n, sizeof(int));
        obj->rank = (int *)calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
                obj->parent[i] = i;
        }
        return obj;
}

int find(const DisjointSet *s, int x) {
        if (s->parent[x] != x) {
                s->parent[x] = find(s, s->parent[x]);
        }
        return s->parent[x];
}

void set_union(DisjointSet *s, int x, int y) {
        int rootx = find(s, x);
        int rooty = find(s, y);
        if (rootx != rooty) {
                if (s->rank[rootx] > s->rank[rooty]) {
                        s->parent[rooty] = rootx;
                } else if (s->rank[rootx] < s->rank[rooty]) {
                        s->parent[rootx] = rooty;
                } else {
                        s->parent[rooty] = rootx;
                        s->rank[rootx]++;
                }
        }
}

bool isLinked(DisjointSet *s, int x, int y) { return find(s, x) == find(s, y); }

bool validPath(int n, int **edges, int edgesSize, int *edgesColSize, int source, int destination) {
        if (source == destination) {
                return true;
        }
        DisjointSet *s = create(n);
        for (int i = 0; i < edgesSize; i++) {
                set_union(s, edges[i][0], edges[i][1]);
        }
        return isLinked(s, source, destination);
}

int main() { return 0; }