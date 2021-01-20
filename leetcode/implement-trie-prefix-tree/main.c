/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-01-20
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

typedef struct _Trie {
        int isEnd;
        struct _Trie *next[26];
} Trie;

/** Initialize your data structure here. */

Trie *trieCreate() {
        Trie *root = (Trie *)malloc(sizeof(Trie));
        memset(root, 0, sizeof(*root));
        root->isEnd = 0;
        return root;
}

/** Inserts a word into the trie. */
void trieInsert(Trie *obj, char *word) {
        Trie *node = obj;

        for (int i = 0; word[i] != '\0'; i++) {
                char c = word[i];
                int idx = c - 'a';
                if (node->next[idx] == NULL) {
                        node->next[idx] = trieCreate();
                }
                node = node->next[idx];
        }
        node->isEnd = 1;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie *obj, char *word) {
        Trie *node = obj;
        for (int i = 0; word[i] != '\0'; i++) {
                char c = word[i];
                int idx = c - 'a';
                if (node->next[idx] == NULL) {
                        return false;
                }
                node = node->next[idx];
        }
        return node->isEnd == 1;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie *obj, char *prefix) {
        Trie *node = obj;
        for (int i = 0; prefix[i] != '\0'; i++) {
                char c = prefix[i];
                int idx = c - 'a';
                if (node->next[idx] == NULL) {
                        return false;
                }
                node = node->next[idx];
        }
        return true;
}

void trieFree(Trie *obj) {
        if (obj == NULL) {
                return;
        }
        for (int i = 0; i < 26; i++) {
                if (obj->next[i] != NULL) {
                        trieFree(obj->next[i]);
                }
        }
        free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
*/

int main() { return 0; }
