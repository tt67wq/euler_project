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

/* https://zyziyun.github.io/2017/03/02/%E9%98%BF%E6%8B%89%E4%BC%AF%E6%95%B0%E5%AD%97%E4%B8%8E%E4%B8%AD%E6%96%87%E6%95%B0%E5%AD%97%E8%BD%AC%E6%8D%A2%E7%AE%97%E6%B3%95/ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

char * Number2Chinese(int num, char **chnNumChar, char **chnUnitSection);
char * Section2Chinese(int);

int main(int ac, char *av[]) {
	int num;
	const char *chnNumChar[10] = {"零", "一", "二", "三", "四",
				      "五", "六", "七", "八", "九"};

	const char *chnUnitSection[] = {"", "万", "亿", "万亿"};
	const char *chnUnitChar[] = {"", "十", "百", "千"};

	/* check args */
	if (ac != 2) {
		fprintf(stderr, "usage: num2chinese num\n");
		exit(1);
	}
        num = atoi(av[1]);
        printf("%d\n", num);
	return 1;
}

char *Number2Chinese(int num, char **chnNumChar, char **chnUnitSection) {
	char *chnStr;
	int unitPos = 0;
	char *strIns;
	int needZero = FALSE;
	int section;

	while (num > 0) {
		section = num % 10000;
		if (needZero) {
			strcat(chnStr, chnNumChar[0]);
		}
		strIns = Section2Chinese(section);
		strcat(strIns,
		       (section != 0) ? chnUnitSection[unitPos] : chnUnitSection[0]);
                chnStr = strcat(strIns, chnStr);
		needZero = (section < 1000)  && (section > 0);
                num = num / 10000;
                ++unitPos;
        }
	return chnStr;
}

char * Section2Chinese(int num){
	char *chnStr;
	char *strIns;
	int unitPos;
        int zero = TRUE;
	int v;

        while (section > 0) {
		v = section % 10;
        }
}
