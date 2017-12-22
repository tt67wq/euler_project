#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

typedef int Type;

struct SkewNode;
typedef struct SkewNode *SkewHeap;

struct SkewNode {
  Type Key;
  SkewHeap Left;
  SkewHeap Right;
};

void preorder_skewheap(SkewHeap heap);
void inorder_skewheap(SkewHeap heap);
void postorder_skewheap(SkewHeap heap);

int skewheap_minimum(SkewHeap heap, int *pval);
SkewHeap merge_skewheap(SkewHeap heap1, SkewHeap heap2);
SkewHeap insert_skewheap(SkewHeap heap, Type x);
SkewHeap pop_skewheap(SkewHeap heap);

void destroy_skewheap(SkewHeap heap);
void print_skewheap(SkewHeap heap);

#endif
