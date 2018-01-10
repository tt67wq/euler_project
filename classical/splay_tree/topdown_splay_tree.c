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

TopDownSplayTree right_right_single_rotate(TopDownSplayTree root) {
  TopDownSplayTree tmp;

  tmp = root;
  root = root->right;
  root->right = root->left;
  root->left = tmp;
  return root;
}

TopDownSplayTree topdown_splay(int value, TopDownSplayTree middle) {
  Node plusTree;
  PNode leftTreeMax;
  PNode rightTreeMin;

  leftTreeMax = &plusTree;
  rightTreeMin = &plusTree;

  while (value != middle->value) {
    if (middle->value < value) {
      if (middle->right == NULL)
        break;
      else if (middle->right->value < value && middle->right->right)
        middle = right_right_single_rotate(middle);
      leftTreeMax->right = middle;
      leftTreeMax = middle;
      middle = middle->right;
      leftTreeMax->right = NULL;
    }
  }
  if (middle->value > value) {
    if (middle->left == NULL)
      break;
    else if (middle->left->value > value && middle->left->left)
      middle = left_left_single_rotate(middle);
    rightTreeMin->left = middle;
    rightTreeMin = middle;
    middle = middle->left;
    rightTreeMin->left = NULL;
  }
  leftTreeMax->right = middle->left;
  rightTreeMin->left = middle->right;
  middle->left = plusTree.right;
  middle->right = plusTree.left;

  return middle;
}
