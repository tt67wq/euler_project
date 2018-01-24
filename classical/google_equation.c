/*
 * =====================================================================================
 *
 *       Filename:  google_equation.c
 *
 *    Description:  谷歌方程式解法
 *
 *        Version:  1.0
 *        Created:  2018-01-24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

/* 题目：有一个由字符组成的等式：WWWDOT - GOOGLE =
 * DOTCOM，每个字符代表一个0~9之间的数字，请找出一组字符和数字的对应关系，使等式成立。
 */

/* 参考解法 */
/* http://www.voidcn.com/article/p-mmzxlpdk-kd.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int count(int used_num[10]);

int main() {
	int w, d, o, t, g, l, e, c, m;
	int i;
	int num1, num2, num3;
	int used_num[10];

}

int count(int used_num[10]) {
	int i;
	int count = 0;
	for (i = 0; i < 10; i++) {
		if (used_num[i] > 0)
			count++;
	}
	return count;
}
