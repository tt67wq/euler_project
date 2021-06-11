/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-11
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
#include <sys/queue.h>
#include <uthash.h>

// 节点间通路。给定有向图，设计一个算法，找出两个节点之间是否存在一条路径。

// 示例1:

//  输入：n = 3, graph = [[0, 1], [0, 2], [1, 2], [1, 2]], start = 0, target = 2
//  输出：true
// 示例2:

//  输入：n = 5, graph = [[0, 1], [0, 2], [0, 4], [0, 4], [0, 1], [1, 3], [1, 4], [1, 3], [2, 3],
//  [3, 4]], start = 0, target = 4 输出 true
// 提示：

// 节点数量n在[0, 1e5]范围内。
// 节点编号大于等于 0 小于 n。
// 图中可能存在自环和平行边

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/route-between-nodes-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct node {
        int elem;
        SIMPLEQ_ENTRY(node) next;
};

SIMPLEQ_HEAD(qhead, node);

struct graphSet {
        int elem;
        int connectsSize;
        int connects[100];
        UT_hash_handle hh; /* makes this structure hashable */
};

bool findWhetherExistsPath(int n, int **graph, int graphSize, int *graphColSize, int start,
                           int target) {
        if (start == target) {
                return true;
        }
        // build connection map
        struct graphSet *set = NULL;

        for (int i = 0; i < graphSize; i++) {

                struct graphSet *s;
                HASH_FIND_INT(set, &(graph[i][0]), s);
                if (s == NULL) {
                        s = (struct graphSet *)malloc(sizeof(struct graphSet));
                        s->elem = graph[i][0];
                        s->connectsSize = 0;
                        s->connects[s->connectsSize++] = graph[i][1];
                        HASH_ADD_INT(set, elem, s);
                } else {
                        int j;
                        for (j = 0; j < s->connectsSize && graph[i][1] != s->connects[j]; j++) {
                        }
                        if (j == s->connectsSize) {
                                s->connects[s->connectsSize++] = graph[i][1];
                        }
                }
        }

        struct qhead *qh = (struct qhead *)malloc(sizeof(struct qhead));
        SIMPLEQ_INIT(qh);

        struct node *_start = (struct node *)malloc(sizeof(struct node));
        _start->elem = start;

        SIMPLEQ_INSERT_HEAD(qh, _start, next);

        while (!SIMPLEQ_EMPTY(qh)) {
                struct node *top = SIMPLEQ_FIRST(qh);
                struct graphSet *s;

                HASH_FIND_INT(set, &(top->elem), s);
                if (s != NULL) {
                        for (int i = 0; i < s->connectsSize; i++) {
                                if (s->connects[i] == target) {
                                        return true;
                                } else {
                                        struct node *_n =
                                            (struct node *)malloc(sizeof(struct node));
                                        _n->elem = s->connects[i];
                                        SIMPLEQ_INSERT_TAIL(qh, _n, next);
                                }
                        }
                }
                SIMPLEQ_REMOVE_HEAD(qh, next);
        }
        return false;
}

int main() {
        int n = 3;
        int _g0[] = {0, 1};
        int _g1[] = {0, 2};
        int _g2[] = {1, 2};
        int _g3[] = {1, 2};
        int *graph[] = {_g0, _g1, _g2, _g3};
        int start = 0;
        int target = 2;

        bool ans =
            findWhetherExistsPath(n, graph, sizeof(graph) / sizeof(graph[0]), NULL, start, target);
        printf("%d\n", ans);

        return 0;
}