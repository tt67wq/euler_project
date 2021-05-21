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

ChineseNum const chnNumMap[10] = {{"零", 0}, {"一", 1}, {"二", 2}, {"三", 3},
                                  {"四", 4}, {"五", 5}, {"六", 6}, {"七", 7},
                                  {"八", 8}, {"九", 9}};

ChineseName const chnNameMap[5] = {{"十", 10, FALSE},
                                   {"百", 100, FALSE},
                                   {"千", 1000, FALSE},
                                   {"万", 10000, TRUE},
                                   {"亿", 100000000, TRUE}};

int chinese2num(char **chnStr, int);
int numHash(char *);
ChineseName nameHash(char *);
int main() {
        char *chn[9] = {"九", "万", "六", "千", "四", "百", "八", "十", "七"};
        printf("%lu\n", LENGTH(chn));
        printf("九万六千四百八十七   转换后结果为: %d\n",
               chinese2num(chn, LENGTH(chn)));
        return 0;
}

int chinese2num(char **chnStr, int size) {
        int rtn = 0;
        int section = 0;
        int number = 0;
        int secUnit = FALSE;
        int i, num, unit;

        for (i = 0; i < size; i++) {
                num = numHash(chnStr[i]);
                printf("num:%d\n", num);
                if (num >= 0) {
                        number = num;
                        if (i == size - 1) {
                                section += number;
                        }
                } else {
                        unit = nameHash(chnStr[i]).value;
                        secUnit = nameHash(chnStr[i]).secUnit;
                        printf("unit: %d, secUnit: %d\n", unit, secUnit);
                        if (secUnit) {
                                section = (section + number) * unit;
                                rtn += section;
                                section = 0;
                        } else {
                                section += (number * unit);
                        }
                        number = 0;
                }
        }
        return rtn + section;
}

int numHash(char *ch) {
        for (int i = 0; i < 10; i++) {
                if (chnNumMap[i].ch == ch) {
                        return chnNumMap[i].num;
                }
        }
        return -1;
}

ChineseName nameHash(char *name) {
        ChineseName cn;
        for (int i = 0; i < 5; ++i) {
                if (chnNameMap[i].ch == name) {
                        return chnNameMap[i];
                }
        }
        cn.ch = "";
        cn.value = 0;
        cn.secUnit = 0;
        return cn;
}
