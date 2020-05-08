/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-08
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

#define MAX_KEY_SIZE 20
#define DEL INT_MIN
#define SIZE 2000
#define HASH_PUT(h, k, v) (put((h), (k), (v)))
#define HASH_GET(h, k, v) (get((h), (k), (v)))
#define HASH_DROP(h, k) (drop((h), (k)))

typedef struct _item {
        char key[MAX_KEY_SIZE];
        int value;
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
                        while (pt) {
                                item *tmp = pt;
                                pt = pt->next;
                                free(tmp);
                        }
                }
        }
        free(hashTable->dicts);
        free(hashTable);
}

bool put(hash *hashTable, char *key, int value) {

        int index = jsHash(key, strlen(key)) % hashTable->size;

        if (hashTable->dicts[index].used) {
                item *pt = hashTable->dicts[index].data;
                bool same = false;
                while (pt) {
                        if (!strcmp(pt->key, key)) {
                                pt->value = value;
                                same = true;
                                break;
                        }
                        pt = pt->next;
                }
                if (!same) {
                        item *tmp = (item *)malloc(sizeof(item));
                        strcpy(tmp->key, key);
                        tmp->value = value;
                        tmp->next = NULL;
                        pt->next = tmp;

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

bool get(hash *hashTable, char *key, int *val) {

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
                                        pt->next = NULL;
                                        free(pt);
                                } else {
                                        free(pt);
                                        hashTable->dicts[index].used = 0;
                                }
                                break;
                        }
                        pre = pt;
                        pt = pt->next;
                }
        }
        return hit;
}

typedef struct {
        hash *hashTable;
        int size;
        int idx;
        int *vals;
} RandomizedSet;

/** Initialize your data structure here. */

RandomizedSet *randomizedSetCreate() {
        srand(50);
        RandomizedSet *rs = (RandomizedSet *)malloc(sizeof(RandomizedSet));
        rs->hashTable = createHash(SIZE);
        rs->idx = 0;
        rs->size = 0;
        rs->vals = (int *)calloc(SIZE, sizeof(int));

        for (int i = 0; i < SIZE; i++) {
                rs->vals[i] = DEL;
        }

        return rs;
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified
 * element. */
bool randomizedSetInsert(RandomizedSet *obj, int val) {
        char key[MAX_KEY_SIZE] = "";
        sprintf(key, "%d", val);

        int idx;
        if (HASH_GET(obj->hashTable, key, &idx)) {
                return false;
        }

        while (obj->vals[obj->idx] != DEL) {
                obj->idx++;
                if (obj->idx == SIZE) {
                        obj->idx = 0;
                }
        }
        obj->vals[obj->idx] = val;
        obj->size++;
        return HASH_PUT(obj->hashTable, key, obj->idx);
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
bool randomizedSetRemove(RandomizedSet *obj, int val) {
        char key[MAX_KEY_SIZE] = "";
        sprintf(key, "%d", val);

        int idx;
        if (HASH_GET(obj->hashTable, key, &idx)) {
                obj->vals[idx] = DEL;
                obj->size--;
                return HASH_DROP(obj->hashTable, key);
        }
        return false;
}

int myRandom(int m) { return rand() % m; }

/** Get a random element from the set. */
int randomizedSetGetRandom(RandomizedSet *obj) {
        int *vals = (int *)malloc(sizeof(int) * obj->size);
        int idx = 0;
        for (int i = 0; i < SIZE; i++) {
                if (obj->vals[i] != DEL) {
                        vals[idx++] = obj->vals[i];
                }
        }
#ifdef DEBUG
        for (int i = 0; i < idx; i++) {
                printf("%d ", vals[i]);
        }
        printf("\n");
#endif
        int ans = vals[myRandom(obj->size)];
        free(vals);
        return ans;
}

void randomizedSetFree(RandomizedSet *obj) {
        disposeHash(obj->hashTable);
        free(obj->vals);
        free(obj);
}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);

 * bool param_2 = randomizedSetRemove(obj, val);

 * int param_3 = randomizedSetGetRandom(obj);

 * randomizedSetFree(obj);
*/

int main() {
        RandomizedSet *rs = randomizedSetCreate();
        printf("insert 0 -> %d\n", randomizedSetInsert(rs, 0));
        printf("insert 1 -> %d\n", randomizedSetInsert(rs, 1));
        printf("remove 0 -> %d\n", randomizedSetRemove(rs, 0));
        printf("insert 2 -> %d\n", randomizedSetInsert(rs, 2));
        printf("remove 1 -> %d\n", randomizedSetRemove(rs, 1));
        printf("getrand -> %d\n", randomizedSetGetRandom(rs));

        randomizedSetFree(rs);
        return 0;
}
