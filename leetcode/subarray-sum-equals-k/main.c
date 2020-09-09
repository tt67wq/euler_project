/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-09
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

#define MAX_KEY_SIZE 20
#define HASH_NEW(s) (createHash((s)))
#define HASH_PUT(h, k, v) (put((h), (k), (v)))
#define HASH_GET(h, k, v) (get((h), (k), (v)))
#define HASH_DROP(h, k) (drop((h), (k)))
#define HASH_FREE(h) (disposeHash((h)))

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

// ----------------- real shit ------------------

void fingerprint(int num, char **fp) { sprintf(*fp, "%d", num); }

void hashIncr(hash *table, char *key) {
        int count = 0;
        if (HASH_GET(table, key, &count)) {
                HASH_PUT(table, key, count + 1);
        } else {
                HASH_PUT(table, key, 1);
        }
}

int subarraySum(int *nums, int numsSize, int k) {
        int pre = 0, ans = 0;
        hash *table = HASH_NEW(0xff);
        char *key = (char *)calloc(MAX_KEY_SIZE, sizeof(char));

        fingerprint(0, &key);
        HASH_PUT(table, key, 1);

        for (int i = 0; i < numsSize; i++) {
                pre += nums[i];
                int count = 0;
                fingerprint(pre - k, &key);
                if (HASH_GET(table, key, &count)) {
                        ans += count;
                } else {
                        ;
                }
                fingerprint(pre, &key);
                hashIncr(table, key);
        }
        HASH_FREE(table);
        free(key);

        return ans;
}

int main() {
        int nums[] = {1, 1, 1};
        int ans = subarraySum(nums, 3, 2);
        printf("%d\n", ans);
        return 0;
}