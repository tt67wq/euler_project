/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-14
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

// 有两个容量分别为 x升 和 y升 的水壶以及无限多的水。
// 请判断能否通过使用这两个水壶，从而可以得到恰好 z升 的水？

// 如果可以，最后请用以上水壶中的一或两个来盛放取得的 z升 水。

// 你允许：

// 装满任意一个水壶
// 清空任意一个水壶
// 从一个水壶向另外一个水壶倒水，直到装满或者倒空
// 示例 1: (From the famous "Die Hard" example)

// 输入: x = 3, y = 5, z = 4
// 输出: True
// 示例 2:

// 输入: x = 2, y = 6, z = 5
// 输出: False

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/water-and-jug-problem
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define SATISFY(a, b, c) (((a) == (c)) || ((b) == (c)) || (((a) + (b)) == (c)))

struct em {
        int c1;
        int c2;
        SIMPLEQ_ENTRY(em) next;
};

SIMPLEQ_HEAD(qh, em);

struct em *_newEm() {
        return (struct em *)malloc(sizeof(struct em));
}

void enqueue(struct qh *q, struct em *node, bool **cache) {
        cache[node->c1][node->c2] = true;
        SIMPLEQ_INSERT_HEAD(q, node, next);
}

bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {

        if SATISFY (jug1Capacity, jug2Capacity, targetCapacity) {
                return true;
        }
        bool **cache = (bool **)calloc(jug1Capacity + 1, sizeof(bool *));
        for (int i = 0; i < jug1Capacity + 1; i++) {
                cache[i] = (bool *)calloc(jug2Capacity + 1, sizeof(bool));
        }

        struct qh *q = (struct qh *)malloc(sizeof(struct qh));
        SIMPLEQ_INIT(q);

        struct em *node = _newEm();
        node->c1 = jug1Capacity;
        node->c2 = jug2Capacity;
        enqueue(q, node, cache);

        while (!SIMPLEQ_EMPTY(q)) {
                struct em *tmp = SIMPLEQ_FIRST(q);
                printf("%d %d\n", tmp->c1, tmp->c2);
                SIMPLEQ_REMOVE_HEAD(q, next);
                // 装满任意一个水壶
                // 清空任意一个水壶
                // 从一个水壶向另外一个水壶倒水，直到装满或者倒空

                // c1
                if (tmp->c1 < jug1Capacity && !cache[jug1Capacity][tmp->c2]) {
                        struct em *child = _newEm();
                        child->c1 = jug1Capacity;
                        child->c2 = tmp->c2;
                        enqueue(q, child, cache);
                }
                if (tmp->c1 > 0 && !cache[0][tmp->c2]) {
                        struct em *child = _newEm();
                        child->c1 = 0;
                        child->c2 = tmp->c2;
                        enqueue(q, child, cache);
                }
                if (tmp->c1 > 0 && tmp->c2 < jug2Capacity) {
                        int d = jug2Capacity - tmp->c2;
                        int _c1 = tmp->c1 > d ? tmp->c1 - d : 0;
                        int _c2 = tmp->c1 > d ? jug2Capacity : tmp->c2 + tmp->c1;
                        if SATISFY (_c1, _c2, targetCapacity) {
                                return true;
                        }

                        if (!cache[_c1][_c2]) {
                                struct em *child = _newEm();
                                child->c1 = _c1;
                                child->c2 = _c2;
                                enqueue(q, child, cache);
                        }
                }

                // c2
                if (tmp->c2 < jug2Capacity && !cache[tmp->c1][jug2Capacity]) {
                        struct em *child = _newEm();
                        child->c1 = tmp->c1;
                        child->c2 = jug2Capacity;
                        enqueue(q, child, cache);
                }

                if (tmp->c2 > 0 && !cache[tmp->c1][0]) {
                        struct em *child = _newEm();
                        child->c1 = tmp->c1;
                        child->c2 = 0;
                        enqueue(q, child, cache);
                }
                if (tmp->c2 > 0 && tmp->c1 < jug1Capacity) {
                        int d = jug1Capacity - tmp->c1;
                        int _c1 = tmp->c2 > d ? jug1Capacity : tmp->c1 + tmp->c2;
                        int _c2 = tmp->c2 > d ? tmp->c2 - d : 0;
                        if SATISFY (_c1, _c2, targetCapacity) {
                                return true;
                        }
                        if (!cache[_c1][_c2]) {
                                struct em *child = _newEm();
                                child->c1 = _c1;
                                child->c2 = _c2;
                                enqueue(q, child, cache);
                        }
                }
        }

        return false;
}

int main() {
        bool res = canMeasureWater(22003, 31237, 1);
        printf("%d\n", res);
        return 0;
}