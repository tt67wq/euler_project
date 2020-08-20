/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-20
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MAX_KEY_SIZE 1000
#define HASH_PUT(h, k, v) (put((h), (k), (v)))
#define HASH_GET(h, k, v) (get((h), (k), (v)))
#define HASH_DROP(h, k) (drop((h), (k)))
#define HASH_FREE(h) (disposeHash((h)))

#define RENDER_FINGERPRINT(fp, a) (sprintf((fp), "%d,%d", (a)[0], (a)[1]))

typedef int vType;

typedef struct _item {
        char key[MAX_KEY_SIZE];
        vType value;
        struct _item *next;
} item;

typedef struct _dict {
        int used;
        item *data;
} dict;

typedef struct hash {
        dict *dicts;
        int size;
} hash;

unsigned int jsHash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash;
}

hash *createHash(int size) {

        hash *hashTable = (hash *)malloc(sizeof(hash));
        hashTable->size = size;
        hashTable->dicts = (dict *)malloc(sizeof(dict) * size);

        for (int i = 0; i < size; i++) {
                hashTable->dicts[i].used = 0;
                hashTable->dicts[i].data = NULL;
        }

        return hashTable;
}

void disposeHash(hash *hashTable) {
        for (int i = 0; i < hashTable->size; i++) {
                if (hashTable->dicts[i].used > 0) {
                        item *pt = hashTable->dicts[i].data;
                        item *pre = NULL;
                        while (pt) {
                                pre = pt;
                                pt = pt->next;
                                free(pre);
                        }
                }
        }
        free(hashTable->dicts);
        free(hashTable);
}

bool put(hash *hashTable, char *key, vType value) {

        int index = jsHash(key, strlen(key)) % hashTable->size;

        if (hashTable->dicts[index].used) {
                item *pt = hashTable->dicts[index].data;
                item *pre = NULL;
                while (pt) {
                        if (!strcmp(pt->key, key)) {
                                pt->value = value;
                                break;
                        }
                        pre = pt;
                        pt = pt->next;
                }
                if (!pt) {
                        item *tmp = (item *)malloc(sizeof(item));
                        strcpy(tmp->key, key);
                        tmp->value = value;
                        tmp->next = NULL;
                        pre->next = tmp;

                        return true;
                } else {
                        return false;
                }
        } else {
                hashTable->dicts[index].data = (item *)malloc(sizeof(item));
                strcpy(hashTable->dicts[index].data->key, key);
                hashTable->dicts[index].data->value = value;
                hashTable->dicts[index].data->next = NULL;
                hashTable->dicts[index].used = 1;
                return true;
        }
}

bool get(hash *hashTable, char *key, vType *val) {

        int index = jsHash(key, strlen(key)) % hashTable->size;
        bool hit = false;
        if (hashTable->dicts[index].used) {
                item *pt = hashTable->dicts[index].data;
                while (pt) {
                        if (strcmp(pt->key, key) == 0) {
                                hit = true;
                                *val = pt->value;
                                break;
                        }
                        pt = pt->next;
                }
        }
        return hit;
}

bool drop(hash *hashTable, char *key) {
        int index = jsHash(key, strlen(key)) % hashTable->size;
        bool hit = false;

        if (hashTable->dicts[index].used) {
                item *pt = hashTable->dicts[index].data;
                item *pre = NULL;

                while (pt) {
                        if (strcmp(pt->key, key) == 0) {
                                hit = true;
                                if (pre) {
                                        pre->next = pt->next;
                                        free(pt);
                                } else {
                                        hashTable->dicts[index].data = pt->next;
                                        if (!pt->next) {
                                                hashTable->dicts[index].used = 0;
                                        }
                                        free(pt);
                                }
                                break;
                        }
                        pre = pt;
                        pt = pt->next;
                }
        } else {
                // not in table
                // pass
        }
        return hit;
}

int cmpfunc(const void *a, const void *b) {
        int fa = (*(int **)a)[0];
        int fb = (*(int **)b)[0];

        if (fa > fb) {
                return 1;
        } else if (fa < fb) {
                return -1;
        }
        return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findRightInterval(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize) {
        hash *table = createHash(MAX_KEY_SIZE);
        int *res = (int *)malloc(sizeof(int) * intervalsSize);
        char fp[10];
        for (int i = 0; i < intervalsSize; i++) {
                RENDER_FINGERPRINT(fp, intervals[i]);
                HASH_PUT(table, fp, i);
        }
        qsort(intervals, intervalsSize, sizeof(intervals[0]), cmpfunc);

        for (int i = 0; i < intervalsSize; i++) {
                int min = INT_MAX;
                int minIndex = -1;
                for (int j = i + 1; j < intervalsSize; j++) {
                        if (intervals[j][0] >= intervals[i][1] && intervals[j][0] < min) {
                                min = intervals[j][0];
                                RENDER_FINGERPRINT(fp, intervals[j]);
                                HASH_GET(table, fp, &minIndex);
                        }
                }
                // int idx = FINGER_PRINT(intervals[i]);
                // res[table[idx]] = minIndex;
                int idx;
                RENDER_FINGERPRINT(fp, intervals[i]);
                HASH_GET(table, fp, &idx);
                res[idx] = minIndex;
        }
        (*returnSize) = intervalsSize;
        HASH_FREE(table);
        return res;
}

int main() {
        // [ [3,4], [2,3], [1,2] ]
        int interval0[] = {3, 4};
        int interval1[] = {2, 3};
        int interval2[] = {1, 2};

        int *intervals[] = {interval0, interval1, interval2};
        int returnSize;
        int *res = findRightInterval(intervals, 3, NULL, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", res[i]);
        }
        printf("\n");
        free(res);

        return 0;
}