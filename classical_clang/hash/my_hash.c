/*
 * =====================================================================================
 *
 *       Filename:  my_hash.c
 *
 *    Description:  写题目用的简单hash表
 *
 *        Version:  1.0
 *        Created:  2019-07-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

unsigned int js_hash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash;
}

void init() {
        int i;
        for (i = 0; i < SIZE; i++) {
                Hash[i] = (dict *)calloc(1, sizeof(dict));
                Hash[i]->used = 0;
        }
}

void clean() {
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
        index = js_hash(key, SIZE) % SIZE;

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

        index = js_hash(key, SIZE) % SIZE;
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

int main() {
        int value;
        char cmd[10];
        char key[MAX_KEY_SIZE];

        init();
        while (scanf("%s", cmd) != EOF) {
                if (!strcmp(cmd, "0")) {
                        break;
                } else if (!strcmp(cmd, "put")) {
                        scanf("%s %d", key, &value);
                        put(key, value);
                } else if (!strcmp(cmd, "get")) {
                        scanf("%s", key);
                        if (get(key, &value))
                                printf("value is %d\n", value);
                        else
                                printf("hash miss\n");
                }
        }
        clean();
        return 0;
}
