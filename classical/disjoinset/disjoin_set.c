/*
 * =====================================================================================
 *
 *       Filename:  disjoin_set.c
 *
 *    Description:  并查集实现
 *
 *        Version:  1.0
 *        Created:  2019-04-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4005

typedef struct {
        int root;
        int rank;
} dset;

dset s[N] = {{0, 0}};

void init() {
        for (int i = 0; i < N; i++) {
                s[i].root = 0;
                s[i].rank = 0;
        }
}

dset find(dset *s, int k) {
        if (s[k].root == 0) {
                // new member
                s[k].root = k;
                s[k].rank = 1;
                return s[k];
        }

        if (s[k].root == k) {
                return s[k];
        }
        s[k] = find(s, s[k].root);

        return s[k];
}

void merge(dset *s, int m, int n) {
        dset ms = find(s, m);
        dset ns = find(s, n);

        // merge small one into big one
        if (ms.rank <= ns.rank) {
                s[ms.root].root = ns.root;
        } else {
                s[ns.root].root = ms.root;
        }
        if (s[ms.root].rank != s[ns.root].rank && s[ms.root].root != s[ns.root].root) {
                s[ns.root].rank++;
        }
}

int main() {
        find(s, 10);
        find(s, 20);
        set_union(s, 10, 20);
        find(s, 30);
        set_union(s, 30, 10);
        printf("%d\n", find(s, 30).root);
        return 0;
}
