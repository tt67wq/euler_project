/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 给定一个平衡括号字符串 S，按下述规则计算该字符串的分数：

// () 得 1 分。
// AB 得 A + B 分，其中 A 和 B 是平衡括号字符串。
// (A) 得 2 * A 分，其中 A 是平衡括号字符串。
//  

// 示例 1：

// 输入： "()"
// 输出： 1
// 示例 2：

// 输入： "(())"
// 输出： 2
// 示例 3：

// 输入： "()()"
// 输出： 2
// 示例 4：

// 输入： "(()(()))"
// 输出： 6
//  

// 提示：

// S 是平衡括号字符串，且只含有 ( 和 ) 。
// 2 <= S.length <= 50

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/score-of-parentheses
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX_SIZE 50
#define LEFT '('
#define RIGHT ')'

typedef struct stack {
        int size;
        char cs[MAX_SIZE];
} stack;

bool isEmpty(stack *st) { return st->size == 0; }
bool push(stack *st, char c) {
        if (st->size >= MAX_SIZE)
                return false;
        st->cs[st->size++] = c;
        return true;
}

bool pop(stack *st, char *c) {
        if (isEmpty(st))
                return false;
        *c = st->cs[st->size--];
        return true;
}

char top(stack *st) { return st->cs[st->size]; }

int scoreOfParentheses(char *s) {
        int l = strlen(s);
        int ans[MAX_SIZE + 1] = {0};
        int lv = 0;

        for (int i = 0; i < l; i++) {
                char c = s[i];
                if (c == LEFT) {
                        lv++;
                        continue;
                }
                if (ans[lv + 1] == 0) {
                        ans[lv] += 1;
                } else {
                        ans[lv] += ans[lv + 1] * 2;
                        ans[lv + 1] = 0;
                }
                lv--;
        }
        return ans[1];
}

int main() {
        char s[] = "(())()";
        printf("%d\n", scoreOfParentheses(s));
        return 0;
}