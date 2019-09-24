/*
 * =====================================================================================
 *
 *       Filename:  hash_table.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "hash_table.h"

uint64_t djb2(char *key) {
        uint64_t hash = 5381;
        int c;
        while ((c = *key++)) {
                hash = ((hash << 5) + hash) + c;
                /* hash = hash * 33 ^ c; */
        }
        return hash;
}

size_t hash_function(struct hash_table *ht, char *key) {
        uint64_t pre_hash = djb2(key);
        return pre_hash & ((1 << ht->M) - 1);
}

it **initialize_bucket(const int size) {
        it **result = malloc(sizeof(it *) * size);
        it **begin = result;
        it **end = begin + size;
        while (begin != end) {
                *begin = NULL;
                ++begin;
        }
        return result;
}

ht *initialize_hash_table(const int M) {
        ht *result = malloc(sizeof(ht));
        result->bucket = initialize_bucket(1 << M);
        result->M = M;
        result->n = 0;
        return result;
}

void push_back(struct item **head_ref, struct item *new_it) {
        if (!(*head_ref)) {
                *head_ref = new_it;
                return;
        }
        it *prev = NULL;
        it *curr = *head_ref;
        while (curr) {
                if (strcmp(curr->key, new_it->key)) {
                        prev = curr;
                        curr = curr->next;
                } else {
                        delete_item(&new_it);
                        ++curr->count;
                        return;
                }
        }
        prev->next = new_it;
}

void insert(struct hash_table **ht_ref, const int n) {
        ++(*ht_ref)->n;
        it *new_item = initialize_item(n);
        size_t idx = hash_function((*ht_ref), new_item->key);
        push_back((*ht_ref)->bucket + idx, new_item);
}

void delete_bucket(struct item **bt_ref) {
        it *prev = NULL;
        it *curr = *bt_ref;
        while (curr) {
                prev = curr;
                curr = curr->next;
                delete_item(&prev);
        }
        *bt_ref = NULL;
}

void delete_hash_table(struct hash_table **ht_ref) {
        it **begin = (*ht_ref)->bucket;
        it **end = begin + (1 << (*ht_ref)->M);
        while (begin != end) {
                if (*begin)
                        delete_bucket(begin);
                ++begin;
        }
        free((*ht_ref)->bucket);
        free(*ht_ref);
        *ht_ref = NULL;
}
