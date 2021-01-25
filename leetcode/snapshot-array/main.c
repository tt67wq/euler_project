/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-01-22
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

#define MAX 50001

typedef struct {
        int set[MAX];
        unsigned short setIndex[MAX];
        unsigned short setIdx;
        unsigned short snap[MAX];
        unsigned short snapid;
} SnapshotArray;

SnapshotArray *snapshotArrayCreate(int length) {
        SnapshotArray *ss = (SnapshotArray *)malloc(sizeof(SnapshotArray));
        memset(ss, 0, sizeof(SnapshotArray));
        return ss;
}

void snapshotArraySet(SnapshotArray *obj, int index, int val) {
        obj->set[obj->setIdx] = val;
        obj->setIndex[obj->setIdx] = index;
        obj->setIdx++;
}

int snapshotArraySnap(SnapshotArray *obj) {
        obj->snap[obj->snapid] = obj->setIdx;
        obj->snapid++;
        return obj->snapid - 1;
}

int snapshotArrayGet(SnapshotArray *obj, int index, int snap_id) {
        for (int i = obj->snap[snap_id] - 1; i >= 0; i--) {
                if (obj->setIndex[i] == index) {
                        return obj->set[i];
                }
        }
        return 0;
}

void snapshotArrayFree(SnapshotArray *obj) { free(obj); }

int main() { return 0; }