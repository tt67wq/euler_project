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

#define N 500

typedef struct {
        int root;
        int size;
} dset;

dset s[N] = {{0, 0}};

dset find(dset *s, int k) {
        if (s[k].root == 0) {
                // new member
                s[k].root = k;
                s[k].size = 1;
                return s[k];
        }
        dset tmp = s[k];
        while (tmp.root != k) {
                k = tmp.root;
                tmp = s[k];
        }
        s[k].root = tmp.root;
        return s[k];
}

void set_union(dset *s, int m, int n) {
        dset mr = find(s, m);
        dset nr = find(s, n);

        // merge small one into big one
        if (mr.size <= nr.size) {
                s[mr.root].root = nr.root;
                s[nr.root].size += mr.size;
        } else {
                s[nr.root].root = mr.root;
                s[mr.root].size += nr.size;
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
