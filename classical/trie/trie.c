/*
 * =====================================================================================
 *
 *       Filename:  trie.c
 *
 *    Description:  前缀树
 *
 *        Version:  1.0
 *        Created:  2019-11-21
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

#define MAX 26   // 26个字母
#define SLEN 1024 // 节点中存储的字符串长度

typedef struct _Trie {
        struct _Trie *next[MAX];
        char s[SLEN]; // 节点处存储的字符串
        int isword;   // 是否为单词
        char val;     // 节点的代表字符
} Trie;

// 初始化Trie树
Trie *init() {
        Trie *root = (Trie *)malloc(sizeof(Trie));
        int i;
        for (i = 0; i < MAX; i++) {
                root->next[i] = NULL;
        }
        root->isword = 0;
        root->val = 0;
        return root;
}

// 按照指定路径path 插入字符串 s
void insert(Trie *root; char path[], char s[]) {
        Trie *t, *p = root;
        int i, j, n = strlen(path);

        for (i = 0; i < n; i++) {
                if (p->next[path[i] - 'a'] == NULL) {
                        t = (Trie *)malloc(sizeof(Trie));
                        for (j = 0; j < MAX; j++) {
                                t->next[j] = NULL;
                                t->isword = 0;
                        }
                        t->val = path[i];
                        p->next[path[i] - 'a'] = t;
                }
                p = p->next[path[i] - 'a'];
        }
        p->isword = 1;
        strcpy(p->s, s);
}

// 按照指定路径 path 查找
char *find(Trie *root; char path[], int delflag) {
        Trie *p = root;
        int i = 0, n = strlen(path);
        while (p && path[i]) {
                p = p->next[path[i++] - 'a'];
        }
        if (p && p->isword) {
                p->isword = delflag;
                return p->s;
        }
        return NULL;
}

//  删除整棵Trie树
void dispose(Trie *root) {
        int i;
        if (!root)
                return;
        for (i = 0; i < MAX; i++) {
                if (root->next[i])
                        dispose(root->next[i]);
                free(root->next[i]);
        }
}

int main() {return 0;}
