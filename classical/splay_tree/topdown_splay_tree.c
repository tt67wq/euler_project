/*
 * =====================================================================================
 *
 *       Filename:  topdown_splay_tree.c
 *
 *    Description:  自顶向下伸展树
 *
 *        Version:  1.0
 *        Created:  2018-01-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* https://github.com/pacosonTang/dataStructure-algorithmAnalysis/blob/master/chapter12/p345_topdown_splay_tree/p345_topdown_splay_tree.c
 */
#include "topdown_splay_tree.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

PNode makeNode(int value) {
  PNode node;
  node = malloc(sizeof(Node));
  if (!node) {
    Error("fail make node");
    return NULL;
  }
  node->left = NULL;
  node->right = NULL;
  node->value = value;
  return node
}

// 左左旋
TopDownSplayTree left_left_single_rotate(TopDownSplayTree root) {
  TopDownSplayTree tmp;

  tmp = root;
  root = root->left;
  root->left = root->right;
  root->right = tmp;
  return root;
}
