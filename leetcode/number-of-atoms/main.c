/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-07-05
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <uthash.h>

// 给定一个化学式formula（作为字符串），返回每种原子的数量。

// 原子总是以一个大写字母开始，接着跟随0个或任意个小写字母，表示原子的名字。

// 如果数量大于 1，原子后会跟着数字表示原子的数量。如果数量等于 1 则不会跟数字。例如，H2O 和 H2O2
// 是可行的，但 H1O2 这个表达是不可行的。

// 两个化学式连在一起是新的化学式。例如 H2O2He3Mg4 也是化学式。

// 一个括号中的化学式和数字（可选择性添加）也是化学式。例如 (H2O2) 和 (H2O2)3 是化学式。

// 给定一个化学式 formula
// ，返回所有原子的数量。格式为：第一个（按字典序）原子的名字，跟着它的数量（如果数量大于 1），
// 然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。

//  

// 示例 1：

// 输入：formula = "H2O"
// 输出："H2O"
// 解释：
// 原子的数量是 {'H': 2, 'O': 1}。
// 示例 2：

// 输入：formula = "Mg(OH)2"
// 输出："H2MgO2"
// 解释：
// 原子的数量是 {'H': 2, 'Mg': 1, 'O': 2}。
// 示例 3：

// 输入：formula = "K4(ON(SO3)2)2"
// 输出："K4N2O14S4"
// 解释：
// 原子的数量是 {'K': 4, 'N': 2, 'O': 14, 'S': 4}。
// 示例 4：

// 输入：formula = "Be32"
// 输出："Be32"

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/number-of-atoms
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX 10
#define IS_DIGIT(a) ((a) >= '0' && (a) <= '9')
#define IS_LETTER(a) ((a) >= 'a' && (a) <= 'z')

struct atomTable {
        char *atom;
        int cnt;
        UT_hash_handle hh;
};

struct frame {
        struct atomTable *table;
        LIST_ENTRY(frame) next;
};

LIST_HEAD(list, frame);

int readNum(char *formula, int *i) {
        if (!IS_DIGIT(formula[*i])) {
                return 1;
        }
        int num = 0;
        while (IS_DIGIT(formula[*i]) && *i < strlen(formula)) {
                num = num * 10 + formula[(*i)++] - '0';
        }
        return num;
}

char *readAtom(char *formula, int *i) {
        char *atom = (char *)calloc(MAX, sizeof(char));
        int idx = 0;
        atom[idx++] = formula[(*i)++];

        while (IS_LETTER(formula[*i]) && *i < strlen(formula)) {
                atom[idx++] = formula[(*i)++];
        }

        return atom;
}

int _sort(struct atomTable *a, struct atomTable *b) { return strcmp(a->atom, b->atom); }

char *countOfAtoms(char *formula) {
        char *ans = (char *)calloc(strlen(formula) * 2, sizeof(char));
        struct list *stack = (struct list *)malloc(sizeof(struct list));
        LIST_INIT(stack);

        // push a empty table to stack

        struct frame *n0 = (struct frame *)malloc(sizeof(struct frame));
        n0->table = NULL;
        LIST_INSERT_HEAD(stack, n0, next);

        for (int i = 0; i < strlen(formula);) {
                char c = formula[i];
                if (c == '(') {
                        i++;
                        // push a empty table to stack
                        struct frame *_n = (struct frame *)malloc(sizeof(struct frame));
                        _n->table = NULL;
                        LIST_INSERT_HEAD(stack, _n, next);
                } else if (c == ')') {
                        i++;
                        // pop top frame
                        // merge top frame
                        int cnt = readNum(formula, &i);

                        struct frame *poped = LIST_FIRST(stack);
                        LIST_REMOVE(poped, next);
                        struct frame *top = LIST_FIRST(stack);

                        struct atomTable *iter;

                        for (iter = poped->table; iter != NULL; iter = iter->hh.next) {
                                iter->cnt *= cnt;

                                struct atomTable *_table = NULL;
                                HASH_FIND_STR(top->table, iter->atom, _table);
                                if (_table) {
                                        _table->cnt += iter->cnt;
                                } else {
                                        // new entry
                                        _table =
                                            (struct atomTable *)malloc(sizeof(struct atomTable));
                                        _table->atom = iter->atom;
                                        _table->cnt = iter->cnt;

                                        HASH_ADD_STR(top->table, atom, _table);
                                }
                        }

                } else {
                        char *atom = readAtom(formula, &i);
                        int cnt = readNum(formula, &i);

                        // update top frame
                        struct frame *top = LIST_FIRST(stack);
                        struct atomTable *_table = NULL;
                        HASH_FIND_STR(top->table, atom, _table);
                        if (_table) {
                                _table->cnt += cnt;
                        } else {
                                // new entry
                                _table = (struct atomTable *)malloc(sizeof(struct atomTable));
                                _table->atom = atom;
                                _table->cnt = cnt;

                                HASH_ADD_STR(top->table, atom, _table);
                        }
                }
        }

        struct frame *res = LIST_FIRST(stack);

        HASH_SORT(res->table, _sort);

        struct atomTable *iter;
        for (iter = res->table; iter != NULL; iter = iter->hh.next) {
                printf("%s: %d\n", iter->atom, iter->cnt);
                if (iter->cnt == 1) {
                        strcat(ans, iter->atom);
                } else {
                        char s[MAX];
                        sprintf(s, "%s%d", iter->atom, iter->cnt);
                        strcat(ans, s);
                }
        }

        return ans;
}

int main() {
        char formula[] = "(Fe10Ds47)34Nh13Bi21Cd7Tc29Ru45Ne33(Ts9He15Cs38Md30Ne23Gd5)15HAl27Eu36("
                         "Ta33Mn25Hg20Ir42Er50Cd5Pa35K)43";
        char *ans = countOfAtoms(formula);
        printf("%s\n", ans);
        return 0;
}