/*
 * =====================================================================================
 *
 *       Filename:  item.c
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

#include "item.h"

uint64_t cube(int n) { return (uint64_t)n * n * n; }

int digit_count(int n) {
        int result = 0;
        while (n) {
                ++result;
                n /= 10;
        }
        return result;
}

char *generate_key(int n) {
        uint64_t x = cube(n);
        char *result = malloc(sizeof(char) * digit_count(n));
        int digit_count[10] = {0};
        while (x) {
                ++digit_count[x % 10];
                x /= 10;
        }
        char *temp = result;
        for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < digit_count[i]; ++j) {
                        *temp = i + '0';
                        ++temp;
                }
        }
        *temp = '\0';
        return result;
}

it *initialize_item(const int n) {
        it *result = malloc(sizeof(it));
        result->data = n;
        result->key = generate_key(n);
        result->count = 1;
        result->next = NULL;
        return result;
}

void delete_item(struct item **it_ref) {
        free((*it_ref)->key);
        (*it_ref)->next = NULL;
        free(*it_ref);
        *it_ref = NULL;
}
