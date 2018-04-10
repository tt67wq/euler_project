/*
 * =====================================================================================
 *
 *       Filename:  nums2chinese.c
 *
 *    Description:  数字转换成中文字符
 *
 *        Version:  1.0
 *        Created:  2018-01-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* 算法的乐趣里面的例子，我把代码补充完整 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

char *const chnNumChar[] = {"零", "一", "二", "三", "四",
                            "五", "六", "七", "八", "九"};
char *const chnUnitSection[] = {"", "万", "亿", "万亿"};
char *const chnUnitChar[] = {"", "十", "百", "千"};

char *Number2Chinese(int num);
char *Section2Chinese(int);
char *join(char *s1, char *s2);

int main(int ac, char *av[]) {
	int num;

	/* check args */
	if (ac != 2) {
		fprintf(stderr, "usage: num2chinese num\n");
		exit(1);
	}
	num = atoi(av[1]);
	printf("输入数字: %d\n", num);
	printf("转换结果: %s\n", Number2Chinese(num));
	return 1;
}

char *Number2Chinese(int num) {
	char *chnStr = "";
	int unitPos = 0;
	char *strIns = "";
	int needZero = FALSE;
	int section;

	while (num > 0) {
		section = num % 10000;
		printf("section: %d\n", section);
		if (needZero) {
			chnStr = join(chnNumChar[0], chnStr);
		}
		strIns = Section2Chinese(section);
		printf("section to chinese: %s\n", strIns);
		strIns = join(strIns,
			      (section != 0) ? chnUnitSection[unitPos] : chnUnitSection[0]);
		chnStr = join(strIns, chnStr);
		needZero = (section < 1000) && (section > 0);
		num = num / 10000;
		++unitPos;
	}
	return chnStr;
}

// 块 转成汉字
char *Section2Chinese(int section) {
	char *chnStr = "";
	char *strIns = "";
	int unitPos = 0;
	int zero = TRUE;
	int v;

	while (section > 0) {
		v = section % 10;
		if (v == 0) {
			if ((section == 0) || !zero) {
				zero = TRUE;
				chnStr = join(chnNumChar[v], chnStr);
			}
		} else {
			zero = FALSE;
			strIns = chnNumChar[v];
			strIns = join(strIns, chnUnitChar[unitPos]);
			chnStr = join(strIns, chnStr);
		}
		unitPos++;
		section = section / 10;
	}
	return chnStr;
}

char *join(char *s1, char *s2) {
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	// in real code you would check for errors in malloc here
	if (result == NULL)
		exit(1);

	strcpy(result, s1);
	strcat(result, s2);

	return result;
}
