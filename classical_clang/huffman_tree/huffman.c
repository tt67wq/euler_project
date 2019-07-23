/*
 * =====================================================================================
 *
 *       Filename:  huffman.c
 *
 *    Description:  霍夫曼树
 *
 *        Version:  1.0
 *        Created:  2019-07-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* 参考资料：http://data.biancheng.net/view/33.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        int weight;              //结点权重
        int parent, left, right; //父结点、左孩子、右孩子在数组中的位置下标
} HTNode, *HuffmanTree;
int main() { return 0; }
