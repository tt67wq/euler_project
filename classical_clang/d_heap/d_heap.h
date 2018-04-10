#ifndef D_HEAP_H
#define D_HEAP_H

struct d_heap_s;
typedef struct d_heap_s *d_heap_pt;
typedef int ElementType;

struct d_heap_s {
  int size;
  int degree;
  int current;
  ElementType *data;
};

/* 索引为i的孩子的索引是 (i*d + j)，其中j = 1, 2, ..., d; */
/* 索引为i的父结点的索引是 (i - 1) / d; */

d_heap_pt initialize(int size, int degree);
void d_heap_free(d_heap_pt heap);
void d_heap_print(d_heap_pt heap);
int d_heap_push(d_heap_pt heap, ElementType x);
ElementType d_heap_pop(d_heap_pt heap);
ElementType d_heap_top(d_heap_pt heap);
int d_heap_empty(d_heap_pt heap);

#endif
