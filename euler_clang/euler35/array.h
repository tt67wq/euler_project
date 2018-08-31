#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdbool.h>

typedef unsigned long long ull;
typedef struct Arr {
        int len;
        int num;
        ull *head;
} A;

void initArr(A *, int);
bool isFull(A *);
bool isEmpty(A *);
bool insert(A *, int, ull);
bool append(A *, ull);
bool remove_arr(A *, int);
void show_arr(A *);
bool inverse(A *);
bool replace(A *, int, ull);

#endif
