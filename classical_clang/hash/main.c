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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#define MAX_KEY_SIZE 20
#define HASH_PUT(h, k, v) (put((h), (k), (v)))
#define HASH_GET(h, k, v) (get((h), (k), (v)))
#define HASH_DROP(h, k) (drop((h), (k)))

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

bool put(hash *hashTable, char *key, vType value) {

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

int main() {
        vType value;
        char cmd[10] = "";
        char key[MAX_KEY_SIZE];

        hash *hashTable = createHash(1000);
        while (scanf("%s", cmd) != EOF) {
                if (!strcmp(cmd, "0")) {
                        break;
                }
                if (!strcmp(cmd, "put")) {
                        scanf("%s %d", key, &value);
                        if (HASH_PUT(hashTable, key, value)) {
                                printf("insert {%s, %d} to hash table\n", key, value);
                        } else {
                                printf("update {%s, %d} to hash table\n", key, value);
                        }
                } else if (!strcmp(cmd, "get")) {
                        scanf("%s", key);
                        if (HASH_GET(hashTable, key, &value)) {
                                printf("value is %d\n", value);
                        } else {
                                printf("hash miss\n");
                        }
                } else if (!strcmp(cmd, "drop")) {
                        scanf("%s", key);
                        if (HASH_DROP(hashTable, key)) {
                                printf("drop %s success\n", key);
                        } else {
                                printf("%s not in hashTable\n", key);
                        }
                }
        }

        disposeHash(hashTable);

        return 0;
}
