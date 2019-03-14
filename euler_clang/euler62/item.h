#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>

typedef struct item {
        int data;
        char *key;
        int count;
        struct item *next;
} it;

uint64_t cube(int n);
char *generate_key(int n);
it *initialize_item(const int n);
void delete_item(struct item **it_ref);

#endif
