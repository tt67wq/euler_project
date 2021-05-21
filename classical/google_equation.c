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

/* 函数指针参考资料 */
/* http://www.cnblogs.com/windlaughing/archive/2013/04/10/3012012.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define SIZE 9
#define USE_MY_ISVALUE 1

typedef struct _ci {
        char key;
        int value;
        int is_leading;
} CharItem;

typedef struct _cv {
        int value;
        int used;
} CharValue;

typedef void (*p_func)(CharItem *);

int is_valid_value(CharItem *, CharValue *);
int make_int_value(CharItem ci[SIZE], char *);
void on_charlist_ready(CharItem ci[SIZE]);
void search_result(CharItem ci[SIZE], CharValue *, int index, p_func);

int main() {
        CharItem ci[SIZE] = {
            {'W', -1, TRUE},  {'D', -1, TRUE},  {'O', -1, FALSE},
            {'T', -1, FALSE}, {'G', -1, TRUE},  {'L', -1, FALSE},
            {'E', -1, FALSE}, {'C', -1, FALSE}, {'M', -1, FALSE}};

        CharValue cv[SIZE + 1] = {
            {0, FALSE}, {1, FALSE}, {2, FALSE}, {3, FALSE}, {4, FALSE},
            {5, FALSE}, {6, FALSE}, {7, FALSE}, {8, FALSE}, {9, FALSE}};

        search_result(ci, cv, 0, on_charlist_ready);
        return 1;
}

int is_valid_value(CharItem *ci, CharValue *cv) {
        /* printf("检测中!\n"); */
        if (cv->value == 0) {  // 如果值为0
                if (USE_MY_ISVALUE) {
                        if (ci->key == 'W' || ci->key == 'G' ||
                            ci->key == 'D')  // 0不能是是开头数字
                                return FALSE;
                } else {
                        return !ci->is_leading;  // true
                }
        }
        return !cv->used;  // 用过的数字返回false
}

int make_int_value(CharItem *ci, char *str) {
        int i, j, res = 0;
        int l = strlen(str);
        for (i = 0; i < l; ++i) {
                for (j = 0; j < SIZE; j++) {
                        if (ci[j].key == str[i]) {
                                res *= 10;
                                res += ci[j].value;
                        }
                }
        }
        return res;
}

void on_charlist_ready(CharItem *ci) {
        char *minuend = "WWWDOT";
        char *subtrahead = "GOOGLE";
        char *diff = "DOTCOM";
        int m, s, d;
        m = make_int_value(ci, minuend);
        s = make_int_value(ci, subtrahead);
        d = make_int_value(ci, diff);
        if ((m - s) == d) printf("%d - %d = %d\n", m, s, d);
}

void search_result(CharItem *ci, CharValue *cv, int index, p_func callback) {
        int max_char_count, max_number_count;
        max_char_count = 9;
        max_number_count = 10;

        if (index == max_char_count) {
                callback(ci);  // 检测是否满足方程
        }

        for (int i = 0; i < max_number_count; ++i) {
                if (is_valid_value(&ci[index], &cv[i])) {
                        cv[i].used = TRUE;
                        ci[index].value = cv[i].value;
                        search_result(ci, cv, index + 1, callback);
                        cv[i].used = FALSE;  // 如果没满足，将used还原
                }
        }
}
