#ifndef _BINQUEUE_H_
#define _BINQUEUE_H_
#define MaxTrees 100
#define Capacity 1000
#define INT_MIN 0

struct BinNode;
struct Collection;
typedef int ElementType;
typedef struct BinNode *Position;
typedef Position BinTree;
typedef struct Collection *BinQueue;

BinTree CombineTrees(BinTree t1, BinTree t2);
BinQueue Merge(BinQueue q1, BinQueue q2);
int IsEmpty(BinQueue q);
BinQueue Initialize();
ElementType DeleteMin(BinQueue q);
BinQueue Insert(ElementType x, BinQueue q);
void PrintQueue(BinQueue Q);

struct BinNode {
  ElementType Element;
  Position LeftChild;
  Position NextSibling;
};

struct Collection {
  int CurrentSize;
  BinTree TheTrees[MaxTrees];
};

#endif
