/*
 * =====================================================================================
 *
 *       Filename:  skew_heap.c
 *
 *    Description:  斜堆的实现
 *
 *        Version:  1.0
 *        Created:  2017-12-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "skew_heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

/*
 *        Name:  swap_skewheap_node
 * Description:  交换两个斜堆
 *
 */
static void swap_skewheap(SkewHeap x, SkewHeap y) {
  SkewHeap tmp;
  tmp = x;
  x = y;
  y = tmp;
}

/*
 *        Name:  merge_skewheap
 * Description:  合并两个堆
 *
(01) 如果一个空斜堆与一个非空斜堆合并，返回非空斜堆。
(02)
如果两个斜堆都非空，那么比较两个根节点，取较小堆的根节点为新的根节点。将"较小堆的根节点的右孩子"和"较大堆"进行合并。
(03) 合并后，交换新堆根节点的左孩子和右孩子。
 */
SkewHeap merge_skewheap(SkewHeap heap1, SkewHeap heap2) {
  if (heap1 == NULL)
    return heap2;
  if (heap2 == NULL)
    return heap1;

  if (heap1->Key > heap2->Key)
    swap_skewheap(heap1, heap2);

  SkewHeap tmp = merge_skewheap(heap1->Right, heap2);
  heap1->Right = heap1->Left;
  heap1->Left = tmp;

  return heap1;
}

/*
 *        Name:  insert_skewheap
 * Description:  往斜堆中插入一个元素
 *
 */
SkewHeap insert_skewheap(SkewHeap heap, Type x) {
  SkewHeap cell;
  cell = checked_malloc(sizeof(struct SkewNode));
  cell->Key = x;
  cell->Left = cell->Right = NULL;

  return merge_skewheap(heap, cell);
}

/*
 *        Name:  pop_skewheap
 * Description:  弹出堆顶
 *
 */
SkewHeap pop_skewheap(SkewHeap heap) {
  SkewHeap l = heap->Left;
  SkewHeap r = heap->Right;

  free(heap);

  return merge_skewheap(l, r);
}

/* 前序遍历 */
void preorder_skewheap(SkewHeap heap) {
  if (heap) {
    printf("%d ", heap->Key);
    preorder_skewheap(heap->Left);
    preorder_skewheap(heap->Right);
  }
}

/* 中序遍历 */
void inorder_skewheap(SkewHeap heap) {
  if (heap) {
    inorder_skewheap(heap->Left);
    printf("%d ", heap->Key);
    inorder_skewheap(heap->Right);
  }
}

/* 后续遍历 */
void postorder_skewheap(SkewHeap heap) {
  if (heap) {
    postorder_skewheap(heap->Left);
    postorder_skewheap(heap->Right);
    printf("%d ", heap->Key);
  }
}

/* 获取最小值 */
int skeheap_minimum(SkewHeap heap, int *pval) {
  if (!heap)
    return -1;

  *pval = heap->Key;
  return 0;
}

/* 销毁堆 */
void destroy_skewheap(SkewHeap heap) {
  if (heap == NULL)
    return;

  if (heap->Left != NULL)
    destroy_skewheap(heap->Left);
  if (heap->Right != NULL)
    destroy_skewheap(heap->Right);
  free(heap);
}

static void skewheap_print(SkewHeap heap, Type key, int direction) {
  if (heap != NULL) {
    if (direction == 0)
      printf("%2d is root\n", heap->Key);
    else
      printf("%2d is %2d's %6s child\n", heap->Key, key,
             direction == 1 ? "right" : "left");
    skewheap_print(heap->Left, heap->Key, -1);
    skewheap_print(heap->Right, heap->Key, 1);
  }
}

void print_skewheap(SkewHeap heap) {
  if (heap != NULL)
    skewheap_print(heap, heap->Key, 0);
}
