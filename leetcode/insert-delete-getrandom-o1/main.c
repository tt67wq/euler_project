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

#define SIZE 1000
#define MAX_KEY_SIZE 20

typedef struct _item {
        char *key;
        int value;
        struct _item *next;
} item;

typedef struct _dict {
        int used;
        item *data;
} dict;

dict *Hash[SIZE];

unsigned int jsHash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash;
}

void initHash() {
        int i;
        for (i = 0; i < SIZE; i++) {
                Hash[i] = (dict *)calloc(1, sizeof(dict));
                Hash[i]->used = 0;
        }
}

void disposeHash() {
        int i;
        item *pt, *tmp;
        for (i = 0; i < SIZE; i++) {
                if (Hash[i]->used) {
                        pt = Hash[i]->data;
                        while (pt) {
                                free(pt->key);
                                tmp = pt;
                                pt = pt->next;
                                free(tmp);
                        }
                        free(Hash[i]);
                }
        }
}

void put(char *key, int value) {
        printf("put {%s, %d} to hash table\n", key, value);
        int index;
        bool same;
        item *tmp, *pt;
        index = jsHash(key, strlen(key)) % SIZE;

        if (Hash[index]->used) {
                pt = Hash[index]->data;
                same = false;
                while (pt) {
                        if (!strcmp(pt->key, key)) {
                                pt->value = value;
                                same = true;
                                break;
                        }
                        pt = pt->next;
                }
                if (!same) {
                        tmp = (item *)calloc(1, sizeof(item));
                        tmp->key = (char *)calloc(MAX_KEY_SIZE, sizeof(char));
                        strcpy(tmp->key, key);
                        tmp->value = value;
                        tmp->next = NULL;
                        pt->next = tmp;
                }
        } else {
                Hash[index]->data = (item *)calloc(1, sizeof(item));
                Hash[index]->data->key = (char *)calloc(MAX_KEY_SIZE, sizeof(char));
                strcpy(Hash[index]->data->key, key);
                Hash[index]->data->value = value;
                Hash[index]->data->next = NULL;
                Hash[index]->used = 1;
        }
}

bool get(char *key, int *val) {
        int index;
        bool hit;
        item *pt;

        index = jsHash(key, strlen(key)) % SIZE;
        hit = false;
        if (Hash[index]->used) {
                pt = Hash[index]->data;
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


typedef struct {
  
} RandomizedSet;

/** Initialize your data structure here. */

RandomizedSet *randomizedSetCreate() {}

/** Inserts a value to the set. Returns true if the set did not already contain the specified
 * element. */
bool randomizedSetInsert(RandomizedSet *obj, int val) {}

/** Removes a value from the set. Returns true if the set contained the specified element. */
bool randomizedSetRemove(RandomizedSet *obj, int val) {}

/** Get a random element from the set. */
int randomizedSetGetRandom(RandomizedSet *obj) {}

void randomizedSetFree(RandomizedSet *obj) {}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);

 * bool param_2 = randomizedSetRemove(obj, val);

 * int param_3 = randomizedSetGetRandom(obj);

 * randomizedSetFree(obj);
*/

int main() { return 0; }
