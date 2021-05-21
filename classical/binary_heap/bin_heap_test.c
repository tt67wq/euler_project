/*
 * =====================================================================================
 *
 *       Filename:  bin_heap_test.c
 *
 *    Description:  测试二叉堆
 *
 *        Version:  1.0
 *        Created:  2017-12-26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "bin_heap.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(void) {
        int a[] = {12, 52, 65, 64, 74, 23, 85, 73, 90};
        printf("排序前: ");
        for (int i = 0; i < LENGTH(a); i++)
                printf("%d ", a[i]);
        printf("\n");
        HeapSort(a, LENGTH(a));
        printf("排序后: ");
        for (int j = 0; j < LENGTH(a); j++)
                printf("%d ", a[j]);
}
