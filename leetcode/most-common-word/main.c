/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-03
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

// #################### real shit ####################

char *mostCommonWord(char *paragraph, char **banned, int bannedSize) {

        hash *word_table = HASH_NEW(1000);
        char **words = (char **)calloc(sizeof(char *), 1000);
        int index = 0;
        char delim[] = " !?',;.";
        char *ans = (char *)calloc(sizeof(char), 11);
        int maxCnt = 0;

        for (char *word = strtok(paragraph, delim); word != NULL; word = strtok(NULL, delim)) {
                // printf("word : %s\n", word);
                for (int i = 0; i < strlen(word); i++) {
                        if (word[i] >= 'A' && word[i] <= 'Z') {
                                word[i] += 'a' - 'A';
                        }
                }
                bool isBanned = false;
                for (int i = 0; i < bannedSize; i++) {
                        if (strcmp(word, banned[i]) == 0) {
                                isBanned = true;
                                break;
                        }
                }
                if (!isBanned) {
                        int cnt = 0;
                        HASH_GET(word_table, word, &cnt);
                        HASH_PUT(word_table, word, cnt + 1);
                        words[index] = (char *)calloc(sizeof(char), 11);
                        strcpy(words[index], word);
                        index++;
                }
        }

        for (int i = 0; i < index; i++) {
                int cnt = 0;
                HASH_GET(word_table, words[i], &cnt);
                if (cnt > maxCnt) {
                        maxCnt = cnt;
                        strcpy(ans, words[i]);
                }
                free(words[i]);
        }

        free(words);
        HASH_FREE(word_table);

        return ans;
}

int main() {
        char paragraph[] = "Bob hit a ball, the hit BALL flew far after it was hit.";
        char ban0[] = "hit";
        char *banned[] = {ban0};
        char *ans = mostCommonWord(paragraph, banned, 1);
        printf("%s\n", ans);
        return 0;
}