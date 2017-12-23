/*
 * =====================================================================================
 *
 *       Filename:  binqueue.c
 *
 *    Description:  二项队列的实现
 *
 *        Version:  1.0
 *        Created:  2017-12-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* http://m.blog.csdn.net/fktr_70/article/details/50445405 */

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )
#define TRUE  1
#define FALSE 0

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}
