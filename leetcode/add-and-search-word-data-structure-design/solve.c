/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-22
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

#define MAX 26   // 26个字母
#define SLEN 100 // 节点中存储的字符串长度

typedef struct _WordDictionary {
        struct _WordDictionary *next[MAX];
        char s[SLEN];
        bool isword;
        char val;

} WordDictionary;

/** Initialize your data structure here. */
WordDictionary *wordDictionaryCreate() {
        WordDictionary *dic;
        int i;
        dic = (WordDictionary *)calloc(1, sizeof(WordDictionary));
        for (i = 0; i < MAX; i++)
                dic->next[i] = NULL;
        dic->isword = false;
        dic->val = 0;
        return dic;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary *obj, char *word) {
        WordDictionary *t, *p = obj;
        int i, j, n = strlen(word);

        for (i = 0; i < n; i++) {
                if (p->next[word[i] - 'a'] == NULL) {
                        t = (WordDictionary *)calloc(1, sizeof(WordDictionary));
                        for (j = 0; j < MAX; j++) {
                                t->next[j] = NULL;
                                t->isword = 0;
                        }
                        t->val = word[i];
                        p->next[word[i] - 'a'] = t;
                }
                p = p->next[word[i] - 'a'];
        }
        p->isword = 1;
        strcpy(p->s, word);
}

bool search(WordDictionary *obj, char *word, int idx) {
        WordDictionary *p = obj;
        int i = idx, n = strlen(word), j;

        while (p && i < n) {
                if (word[i] == '.') {
                        for (j = 0; j < MAX; j++) {
                                if (p->next[j] != NULL)
                                        if (search(p->next[j], word, idx + 1))
                                                return true;
                        }
                        return false;
                } else {
                        p = p->next[word[i++] - 'a'];
                        idx++;
                }
        }

        if (p && p->isword)
                return true;

        return false;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary *obj, char *word) { return search(obj, word, 0); }

void wordDictionaryFree(WordDictionary *obj) {
        int i;
        if (!obj)
                return;
        for (i = 0; i < MAX; i++) {
                if (obj->next[i])
                        wordDictionaryFree(obj->next[i]);
                free(obj->next[i]);
        }
}

int main() {return 0;}
