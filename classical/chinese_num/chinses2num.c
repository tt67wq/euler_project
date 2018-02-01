/*
 * =====================================================================================
 *
 *       Filename:  chinses2num.c
 *
 *    Description:  中文转阿拉伯数字
 *
 *        Version:  1.0
 *        Created:  2018-02-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* https://segmentfault.com/a/1190000004881457 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

typedef struct _chn {
	char *ch;
	int num;
} ChineseNum;

typedef struct _chs {
	char *ch;
	int value;
	int secUnit;
} ChineseName;

ChineseNum const chnNumMap[10] = {{"零", 0}, {"一", 0}, {"二", 0}, {"三", 0},
                                  {"四", 0}, {"五", 0}, {"六", 0}, {"七", 0},
                                  {"八", 0}, {"九", 0}};

ChineseName const chnNameMap[5] = {{"十", 10, FALSE},
                                  {"百", 100, FALSE},
                                  {"千", 1000, FALSE},
                                  {"万", 10000, TRUE},
                                  {"亿", 100000000, FALSE}};

int main() { return 0; }
