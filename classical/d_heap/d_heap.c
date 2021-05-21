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
#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

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
  while (k > 0 && item_cmp(heap->data[(k - 1) / degree], heap->data[k])) {
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

int d_heap_push(d_heap_pt heap, ElementType x) {
  if (heap == NULL)
    return 0;
  if (heap->current == heap->size)
    return 0;
  heap->data[heap->current] = x;
  fixup(heap, heap->current++);
  return 1;
}

ElementType d_heap_pop(d_heap_pt heap) {
  swap(heap->data, 0, heap->current - 1);
  fixdown(heap, 0, heap->current - 2);
  return heap->data[--heap->current];
}

ElementType d_heap_top(d_heap_pt heap) { return heap->data[0]; }
int d_heap_empty(d_heap_pt heap) { return heap->current == 0; }

int main(int argc, char *argv[]) {
  int a[] = {10, 20, 30, 50, 40, 70, 100, 130, 150, 60, 80, 170, 90, 110, 90};
  int i, len = LENGTH(a);
  d_heap_pt heap = NULL;
  heap = initialize(LENGTH(a) + 10, 3);

  printf("\n== 空堆检查: %d", d_heap_empty(heap));
  printf("\n== 插入数据: ");
  for (i = 0; i < len; i++) {
    printf("%d ", a[i]);
    d_heap_push(heap, a[i]);
  }
  printf("\n== 空堆检查: %d", d_heap_empty(heap));

  printf("\n== 最 小 堆: ");
  d_heap_print(heap);

  i = 15;
  d_heap_push(heap, i);
  printf("\n== 添加元素: %d", i);
  printf("\n== 最 小 堆: ");
  d_heap_print(heap);

  printf("\n== 堆顶元素: %d\n", d_heap_top(heap));

  i = d_heap_pop(heap);
  printf("\n== 删除元素: %d", i);
  printf("\n== 最 小 堆: ");
  d_heap_print(heap);
  printf("\n");
  i = d_heap_pop(heap);
  printf("\n== 删除元素: %d", i);
  printf("\n== 最 小 堆: ");
  d_heap_print(heap);
  printf("\n");
  d_heap_free(heap);
  return 0;
}
