/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-09
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

// 给你一个字符串 s 以及两个整数 a 和 b 。其中，字符串 s 的长度为偶数，且仅由数字 0 到 9 组成。

// 你可以在 s 上按任意顺序多次执行下面两个操作之一：

// 累加：将  a 加到 s 中所有下标为奇数的元素上（下标从 0 开始）。
// 数字一旦超过 9 就会变成 0，如此循环往复。例如，s = "3456" 且 a = 5，则执行此操作后 s 变成
// "3951"。 轮转：将 s 向右轮转 b 位。例如，s = "3456" 且 b = 1，则执行此操作后 s 变成 "6345"。
// 请你返回在 s 上执行上述操作任意次后可以得到的 字典序最小 的字符串。

// 如果两个字符串长度相同，那么字符串 a 字典序比字符串 b 小可以这样定义：在 a 和 b
// 出现不同的第一个位置上， 字符串 a 中的字符出现在字母表中的时间早于 b 中的对应字符。 例如，"0158”
// 字典序比 "0190" 小，因为不同的第一个位置是在第三个字符，显然 '5' 出现在 '9' 之前。

// 示例 1：

// 输入：s = "5525", a = 9, b = 2
// 输出："2050"
// 解释：执行操作如下：
// 初态："5525"
// 轮转："2555"
// 累加："2454"
// 累加："2353"
// 轮转："5323"
// 累加："5222"
// 累加："5121"
// 轮转："2151"
// 累加："2050"​​​​​​​​​​​​
// 无法获得字典序小于 "2050" 的字符串。
// 示例 2：

// 输入：s = "74", a = 5, b = 1
// 输出："24"
// 解释：执行操作如下：
// 初态："74"
// 轮转："47"
// 累加："42"
// 轮转："24"​​​​​​​​​​​​
// 无法获得字典序小于 "24" 的字符串。
// 示例 3：

// 输入：s = "0011", a = 4, b = 2
// 输出："0011"
// 解释：无法获得字典序小于 "0011" 的字符串。
// 示例 4：

// 输入：s = "43987654", a = 7, b = 3
// 输出："00553311"
//  

// 提示：

// 2 <= s.length <= 100
// s.length 是偶数
// s 仅由数字 0 到 9 组成
// 1 <= a <= 9
// 1 <= b <= s.length - 1

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/lexicographically-smallest-string-after-applying-operations
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct node {
        char *ss;
        SIMPLEQ_ENTRY(node) next;
};

SIMPLEQ_HEAD(head, node);

struct stable {
        char *ss;
        UT_hash_handle hh; /* makes this structure hashable */
};

void rotate_right(char *ss, char *sd, int sl, int b) {
        for (int i = 0; i < sl - b; i++) {
                sd[i + b] = ss[i];
        }
        for (int i = sl - b; i < sl; i++) {
                sd[i - sl + b] = ss[i];
        }
}

void add_odds(char *ss, int sl, int a) {
        for (int i = 1; i < sl; i += 2) {
                ss[i] = (ss[i] - '0' + a) % 10 + '0';
        }
}

char *new_str(int size) {
        char *r = (char *)malloc(sizeof(char) * (size + 1));
        r[size] = '\0';
        return r;
}

char *findLexSmallestString(char *s, int a, int b) {
        int sl = strlen(s);
        char *ans = new_str(sl);
        strcpy(ans, s);

        // queue
        struct head *q = (struct head *)malloc(sizeof(struct head));
        SIMPLEQ_INIT(q);

        // hash
        struct stable *hash = NULL;
        struct stable *en0 = (struct stable *)malloc(sizeof(struct stable));
        en0->ss = s;

        HASH_ADD_STR(hash, ss, en0);

        struct node *n0 = (struct node *)malloc(sizeof(struct node));
        n0->ss = s;

        SIMPLEQ_INSERT_TAIL(q, n0, next);

        struct stable *tmp;
        while (!SIMPLEQ_EMPTY(q)) {
                struct node *nt = SIMPLEQ_FIRST(q);
                SIMPLEQ_REMOVE_HEAD(q, next);

                // compare
                if (strcmp(nt->ss, ans) < 0) {
                        strcpy(ans, nt->ss);
                }

                // rotate
                char *s1 = new_str(sl);
                rotate_right(nt->ss, s1, sl, b);
                HASH_FIND_STR(hash, s1, tmp);
                if (tmp == NULL) {
                        struct node *n1 = (struct node *)malloc(sizeof(struct node));
                        n1->ss = s1;
                        SIMPLEQ_INSERT_TAIL(q, n1, next);

                        struct stable *en1 = (struct stable *)malloc(sizeof(struct stable));
                        en1->ss = s1;
                        HASH_ADD_STR(hash, ss, en1);
                }

                // add odds
                char *s2 = new_str(sl);
                strcpy(s2, nt->ss);
                add_odds(s2, sl, a);
                HASH_FIND_STR(hash, s2, tmp);
                if (tmp == NULL) {
                        struct node *n2 = (struct node *)malloc(sizeof(struct node));
                        n2->ss = s2;
                        SIMPLEQ_INSERT_TAIL(q, n2, next);

                        struct stable *en2 = (struct stable *)malloc(sizeof(struct stable));
                        en2->ss = s2;
                        HASH_ADD_STR(hash, ss, en2);
                }
        }
        return ans;
}

int main() {
        char s[] = "5525";
        puts(findLexSmallestString(s, 9, 2));
        return 0;
}