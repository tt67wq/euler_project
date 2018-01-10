#ifndef _TopdownSplayTree_
#define _TopdownSplayTree_

#define Error(str) printf("\n\t error: %s\n", str)

typedef struct _Node {
  int value;
  struct _Node *left;
  struct _Node *right;
} Node, *PNode, *TopDownSplayTree;

void printPreorder(int depth, TopDownSplayTree root);
TopDownSplayTree topdown_splay(int value, TopDownSplayTree);
Node makeNode(int);
TopDownSplayTree left_left_single_rotate(TopDownSplayTree);
TopDownSplayTree right_right_single_rotate(TopDownSplayTree);
TopDownSplayTree insert(int value, TopDownSplayTree root);
TopDownSplayTree deleteNode(int value, TopDownSplayTree root);
#endif
