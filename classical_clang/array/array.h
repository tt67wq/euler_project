#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdbool.h>

typedef struct Arr {
        int len;
        int num;
        int *head;
} A;

void initArr(A *, int);
bool isFull(A *);
bool isEmpty(A *);
bool insert(A *, int, int);
bool append(A *, int);
bool remove_arr(A *, int);
void show_arr(A *);
bool inverse(A *);
bool replace(A *, int, int);

#endif
