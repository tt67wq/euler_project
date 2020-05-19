/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-19
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

#define DEBUG

/**
 * *********************************************************************
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int get(MountainArray *, int index);
 * int length(MountainArray *);
 */

struct MountainArray {
        int *data;
        int len;
};

typedef struct MountainArray MountainArray;

int get(MountainArray *m, int index) { return m->data[index]; }
int length(MountainArray *m) { return m->len; }

int findInMountainArray(int target, MountainArray *m) {

        // search peak
        int s = 0;
        int e = length(m);
        int pidx = 0;
        int peak = 0;
        bool flag = true;

        while ((s < e) && flag) {
                int mid = (s + e) / 2;
                if (mid == s) {
                        flag = false;
                }
                int a = get(m, mid);
                int b = get(m, mid - 1);
                int c = get(m, mid + 1);

                if (a > b && a > c) {
                        // is peak
                        peak = a;
                        pidx = mid;
                        break;
                } else if (a > b && a < c) {
                        // climb
                        s = mid;
                } else if (a < b && a > c) {
                        // down
                        e = mid;
                }
        }

        if (target == peak) {
                return pidx;
        }

#ifdef DEBUG
        printf("peak->%d peak_idx->%d\n", peak, pidx);
#endif

        // search left
        s = 0;
        e = pidx;
        flag = true;
        do {
                int mid = (s + e) / 2;
                if (mid == s) {
                        flag = false;
                }
                int a = get(m, mid);

                if (a < target) {
                        s = mid;
                } else if (a > target) {
                        e = mid;
                } else {
                        return mid;
                }
        } while ((s < e) && flag);

        // search right
        s = pidx;
        e = length(m);
        flag = true;

        do {
                int mid = (s + e) / 2;
                if (mid == s) {
                        flag = false;
                }
                int a = get(m, mid);

                if (a < target) {
                        e = mid;
                } else if (a > target) {
                        s = mid;
                } else {
                        return mid;
                }
        } while ((s < e) && flag);

        return -1;
}

int main() {
        MountainArray m;
        int data[] = {1, 2, 5, 1};
        m.data = data;
        m.len = 4;

        printf("%d\n", findInMountainArray(1, &m));

        return 0;
}
