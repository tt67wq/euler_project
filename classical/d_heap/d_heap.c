/*
 * =====================================================================================
 *
 *       Filename: d_heap.c
 *
 *    Description: D堆实现
 *
 *        Version:  1.0
 *        Created:  2017-12-20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

/* http://mingnote.com/d-heap-algorithm-in-c.html */
#include "d_heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define item_cmp(a, b) ((a) > (b)) /* 最小堆 */

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

static void swap(ElementType *data, int a, int b) {
  ElementType c;
  c = data[a];
  data[a] = data[b];
  data[b] = c;
}

/*
 *        Name:  fixup
 * Description:  向上堆化
 *
 */
static void fixup(d_heap_pt heap, int k) {
  int degree = heap->degree;
  while (k > 0 && item_cmp(heap->data[(k - 1) / degree, heap->data[k]])) {
    swap(heap->data, k, (k - 1) / degree);
    k = (k - 1) / degree;
  }
}

/*
 *        Name:  fixdown
 * Description:  向下堆化
 *
 */
static void fixdown(d_heap_pt heap, int k, int end) {
  int temp, tail, i;
  int degree = heap->degree;

  while (k * degree + 1 <= end) {
    tail = k * degree + degree;
    tail = tail < end ? tail : end;
    for (i = k * degree + 1, temp = i; i < tail; i++) {
      if (item_cmp(heap->data[temp], heap->data[i]))
        temp = i;
    }
    if (!item_cmp(heap->data[k], heap->data[temp]))
      break;
    swap(heap->data, k, temp);
    k = temp;
  }
}

/*
 *        Name:  initialize
 * Description:  初始化
 *
 */
d_heap_pt initialize(int size, int degree) {
  d_heap_pt heap_pt;
  if (size <= 0)
    return NULL;

  heap_pt = checked_malloc(sizeof(struct d_heap_s));
  heap_pt->data = checked_malloc(sizeof(ElementType) * size);
  heap_pt->size = size;
  heap_pt->degree = degree;
  heap_pt->current = 0;
  return heap_pt;
}

void d_heap_free(d_heap_pt heap) {
  if (heap == NULL)
    return;
  free(heap->data);
  free(heap);
}

void d_heap_print(d_heap_pt heap) {
  int i;
  if (heap == NULL)
    return;
  for (i = 0; i < heap->size; i++)
    printf("%d ", heap->data[i]);
}
