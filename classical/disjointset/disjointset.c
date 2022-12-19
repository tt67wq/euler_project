/*
 * =====================================================================================
 *
 *       Filename:  disjointset.c
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

#include <stdio.h>
#include <stdlib.h>

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
