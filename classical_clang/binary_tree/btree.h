#ifndef __BTREE_H__
#define __BTREE_H__

// 二叉树结构定义
struct _btr_node {
        int id;
        int value;
        struct _btr_node *child[2];
};
typedef struct _btr_node btr_node;

#endif
