#ifndef _TopDownSplayTree_
#define _TopDownSplayTree_

typedef struct _node {
  int data;
  struct _node *parent;
  struct _ndoe *left;
  struct _node *right;
} node;

int data_print(node *x);
node *rightrotation(node *p, node *root);
node *leftrotation(node *p, node *root);
void splay(node *x, node *root);
node *insert(node *p, int value);
node *inorder(node *p);
node *delete (node *p, int value);
node *successor(node *x);
node *lookup(node *p, int value);

#endif
