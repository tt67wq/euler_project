#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stdio.h>
#include <string.h>

#include "item.h"

typedef struct hash_table {
        struct item **bucket;
        int M;
        int n;
} ht;

uint64_t djb2(char *key);
size_t hash_function(struct hash_table *ht, char *key);
it **initialize_bucket(const int size);
ht *initialize_hash_table(const int M);
void push_back(struct item **bt_ref, struct item *new_it);
void insert(struct hash_table **ht_ref, const int n);
void delete_bucket(struct item **bt_ref);
void delete_hash_table(struct hash_table **ht_ref);

#endif
