/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-09
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

#define DEBUG

struct Node {
        int val;
        int numNeighbors;
        struct Node **neighbors;
};

struct Node **nodes;
int *state; //数组存放结点状态 0：结点未创建 1：仅创建结点 2：结点已创建并已填入所有内容

void bfs(struct Node *s) {
        if (nodes[s->val]) {
                if (state[s->val] == 2) {
                        ;
                }
                if (state[s->val] == 1) {
                        int i;
                        struct Node *nd = nodes[s->val];
                        nd->val = s->val;
                        nd->numNeighbors = s->numNeighbors;
                        nd->neighbors =
                            (struct Node **)malloc(sizeof(struct Node *) * nd->numNeighbors);
                        for (i = 0; i < nd->numNeighbors; i++) {
                                if (nodes[s->neighbors[i]->val]) {
                                        nd->neighbors[i] = nodes[s->neighbors[i]->val];
                                } else {
                                        nodes[s->neighbors[i]->val] =
                                            (struct Node *)malloc(sizeof(struct Node));
                                        state[s->neighbors[i]->val] = 1;
                                        nd->neighbors[i] = nodes[s->neighbors[i]->val];
                                }
                        }
                        state[nd->val] = 2;
                }
        } else {
                int i;
                struct Node *nd = (struct Node *)malloc(sizeof(struct Node));
                nd->val = s->val;
                nd->numNeighbors = s->numNeighbors;
                nd->neighbors = (struct Node **)malloc(sizeof(struct Node *) * nd->numNeighbors);
                nodes[s->val] = nd;
                for (i = 0; i < nd->numNeighbors; i++) {
                        if (nodes[s->neighbors[i]->val]) {
                                nd->neighbors[i] = nodes[s->neighbors[i]->val];
                        } else {
                                nodes[s->neighbors[i]->val] =
                                    (struct Node *)malloc(sizeof(struct Node));
                                state[s->neighbors[i]->val] = 1;
                                nd->neighbors[i] = nodes[s->neighbors[i]->val];
                        }
                }
                state[nd->val] = 2;
        }
}

struct Node *cloneGraph(struct Node *s) {
        if (s == NULL) {
                return NULL;
        }
        struct Node *QUEUE[101], *p;
        int head = -1, end = -1, i, flag[101];

        nodes = (struct Node **)malloc(sizeof(struct Node *) * 101);
        memset(nodes, 0, sizeof(struct Node *) * 101);
        state = (int *)malloc(sizeof(int) * 101);
        memset(state, 0, sizeof(int) * 101);
        memset(flag, 0, sizeof(int) * 101);

        QUEUE[++end] = s;
        while (head != end) {
                p = QUEUE[++head];
                bfs(p);
                for (i = 0; i < p->numNeighbors; i++) {
                        if (!flag[p->neighbors[i]->val]) {
                                QUEUE[++end] = p->neighbors[i];
                                flag[p->neighbors[i]->val] = 1;
                        }
                }
        }
        return nodes[s->val];
}

int main() {
        struct Node a;
        a.val = 1;
        a.numNeighbors = 1;

        struct Node b;
        b.val = 2;
        b.numNeighbors = 1;

        a.neighbors = (struct Node **)malloc(sizeof(struct Node *));
        b.neighbors = (struct Node **)malloc(sizeof(struct Node *));

        a.neighbors[0] = &b;
        b.neighbors[0] = &a;

        cloneGraph(&a);

        return 0;
}
