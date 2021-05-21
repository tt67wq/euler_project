/*
 * =====================================================================================
 *
 *       Filename:  bst.c
 *
 *    Description:  二叉查找树
 *
 *        Version:  1.0
 *        Created:  2019-07-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
        int key;
        struct _node *left;
        struct _node *right;
        struct _node *parent;
} node, *bstree;

node *bstree_successor(node *x);

static node *create_bstree_node(int key, node *parent, node *left, node *right) {
        node *p;
        p = (node *)calloc(1, sizeof(node));
        p->key = key;
        p->left = left;
        p->right = right;
        p->parent = parent;

        return p;
}

static node *bstree_insert(bstree tr, node *x) {
        node *y = NULL;
        node *z = tr;
        while (z != NULL) {
                y = z;
                if (x->key < z->key)
                        z = z->left;
                else
                        z = z->right;
        }

        x->parent = y;
        if (y == NULL)
                tr = x;
        else if (x->key < y->key)
                y->left = x;
        else
                y->right = x;
        return tr;
}

static node *bstree_delete(bstree tr, node *x) {
        node *y = NULL;
        node *z = NULL;

        if (x->left == NULL || x->right == NULL)
                y = x;
        else
                y = bstree_successor(x);

        if (y->left != NULL)
                z = y->left;
        else
                z = y->right;

        if (z != NULL)
                z->parent = y->parent;

        if (y->parent == NULL)
                tr = z;
        else if (y == y->parent->left)
                y->parent->left = z;
        else
                y->parent->right = z;

        if (y != x)
                x->key = y->key;

        if (y != NULL)
                free(y);

        return tr;
}

node *bstree_search(bstree tr, int key) {
        if (tr == NULL || tr->key == key)
                return tr;

        if (key < tr->key)
                return bstree_search(tr->left, key);
        else
                return bstree_search(tr->right, key);
}

node *bstree_maximum(bstree tr) {
        if (tr == NULL)
                return tr;
        while (tr->right != NULL)
                tr = tr->right;
        return tr;
}

node *bstree_minimum(bstree tr) {
        if (tr == NULL)
                return tr;
        while (tr->left != NULL)
                tr = tr->left;
        return tr;
}
node *bstree_predecessor(node *x) {
        if (x->left != NULL)
                return bstree_maximum(x->left);

        node *y = x->parent;
        while ((y != NULL) && (x == y->left)) {
                x = y;
                y = y->parent;
        }
        return y->parent;
}

node *bstree_successor(node *x) {
        if (x->right != NULL)
                return bstree_minimum(x->right);

        node *y = x->parent;
        while (y != NULL && x == y->right) {
                x = y;
                y = y->parent;
        }
        return y;
}

node *insert_bstree(bstree tr, int key) {
        node *x;
        x = create_bstree_node(key, NULL, NULL, NULL);
        return bstree_insert(tr, x);
}

node *delete_bstree(bstree tr, int key) {
        node *x;
        x = bstree_search(tr, key);
        tr = bstree_delete(tr, x);
        return tr;
}

int main() { return 0; }
