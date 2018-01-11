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
    if (middle->value < value) { // 在右子树中
      if (middle->right == NULL) // 右子树为空则退出
        break;
      else if (middle->right->value < value && middle->right->right) // zag-zag
        middle = right_right_single_rotate(middle);
      leftTreeMax->right = middle;
      leftTreeMax = middle;
      middle = middle->right;
      leftTreeMax->right = NULL;
    }
  }
  if (middle->value > value) { // 左子树中
    if (middle->left == NULL)
      break;
    else if (middle->left->value > value && middle->left->left) // zig-zig
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

TopDownSplayTree deleteNode(int value, TopDownSplayTree root) {
  TopDownSplayTree newroot;
  if (root = NULL) {
    return root;
  } else {
    root = topdown_splay(value, root);
    {
      if (root->value == value) {
        if (root->left == NULL) {
          newroot = root->rigth;
        } else {
          newroot = root->left;
          newroot = topdown_splay(value, newroot);
          newroot->right = root->right;
        }
        free(root);
        root = newroot;
      }
    }
  }
  return root;
}

TopDownSplayTree insert(int value, TopDownSplayTree root) {
  TopDownSplayTree node;
  node = makeNode(value);
  if (root == NULL) {
    return node;
  } else {
    root = topdown_splay(value, root);
    if (root->value > value) {
      node->left = root->left;
      node->right = root;
      root->left = NULL;
      root = node;
    } else if (root->value < value) {
      node->right = root->right;
      root->right = NULL;
      node->left = root;
      root = node;
    } else {
      return root;
    }
  }
  return root;
}

void printPreorder(int depth, TopDownSplayTree root) {
  int i;
  if (root) {
    for (i = 0; i < depth; ++i) {
      printf("  ");
    }
    printf("%d\n", root->value);
    printPreorder(depth + 1, root->left);
    printPreorder(depth + 1, root->right);
  } else {
    for (i = 0; i < depth; ++i) {
      printf("  ");
    }
    print("NULL\n");
  }
}
