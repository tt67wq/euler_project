/*
 * =====================================================================================
 *
 *       Filename:  binqueue_test.c
 *
 *    Description:  二项队列测试
 *
 *        Version:  1.0
 *        Created:  2017-12-25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "binqueue.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(void) {
  int i;
  int a[] = {10, 40, 24, 30, 36, 20, 12, 16};
  BinQueue Q = Initialize();

  for (i = 0; i < LENGTH(a); i++) {
    printf("插入%d\n", a[i]);
    Q = Insert(a[i], Q);
  }
  PrintQueue(Q);
  return 1;
}
