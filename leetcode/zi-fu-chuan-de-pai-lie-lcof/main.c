/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-23
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */
// 输入一个字符串，打印出该字符串中字符的所有排列。

//  

// 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

//  

// 示例:

// 输入：s = "abc"
// 输出：["abc","acb","bac","bca","cab","cba"]
//  

// 限制：

// 1 <= s 的长度 <= 8

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

struct elem {
        char *ss;
        LIST_ENTRY(elem) next;
};

LIST_HEAD(lhead, elem);

int cmpfunc(const void *a, const void *b) { return (*(char *)a - *(char *)b); }

void _perm(char *s, int slen, int index, struct lhead *lh, char *res, int *cnt, int *size) {
        if (index == slen) {
                // printf("%s\n", res);
                char *ss = (char *)calloc(slen + 1, sizeof(char));
                strcpy(ss, res);
                struct elem *_e = (struct elem *)malloc(sizeof(struct elem));
                _e->ss = ss;
                LIST_INSERT_HEAD(lh, _e, next);
                (*size)++;
                return;
        }

        for (int i = 0; i < slen;) {
                if (cnt[s[i] - 'a'] == 0) {
                        i++;
                        continue;
                }
                cnt[s[i] - 'a']--;
                res[index] = s[i];
                _perm(s, slen, index + 1, lh, res, cnt, size);
                cnt[s[i] - 'a']++;

                while (i + 1 < slen && s[i + 1] == s[i]) {
                        i++;
                }
                i++;
        }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **permutation(char *s, int *returnSize) {

        int slen = strlen(s);
        struct lhead *lh = (struct lhead *)malloc(sizeof(struct lhead));
        LIST_INIT(lh);
        char *res = (char *)calloc(slen + 1, sizeof(char));
        int cnt[26] = {0};

        // sort s
        qsort(s, slen, sizeof(char), cmpfunc);

        // cnt
        for (int i = 0; i < slen; i++) {
                cnt[s[i] - 'a']++;
        }

        *returnSize = 0;
        _perm(s, slen, 0, lh, res, cnt, returnSize);

        char **ans = (char **)calloc(*returnSize, sizeof(char *));

        int i = 0;
        while (!LIST_EMPTY(lh)) {
                struct elem *_e = LIST_FIRST(lh);
                ans[i++] = _e->ss;
                LIST_REMOVE(_e, next);
        }
        return ans;
}

int main() {
        char s[] = "abc";

        permutation(s, NULL);
        return 0;
}