/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-12
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
#include <time.h>

#define SKIPLIST_MAXLEVEL 10

typedef struct SkiplistNode {
        int score;
        struct SkiplistNode *backword;
        struct SkiplistLevel {
                struct SkiplistNode *forward;
        } level[];
} SkiplistNode;

typedef struct {
        struct SkiplistNode *header, *tail;
        unsigned long length;
        int level;
} Skiplist;

int slRandomLevel() {

        int level = 1;
        while ((rand() & 0xFFFF) < (0.5 * 0xFFFF)) {
                ++level;
        }
        return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
}

SkiplistNode *slCreateNode(int level, int score) {
        SkiplistNode *sn = malloc(sizeof(SkiplistNode) + level * sizeof(struct SkiplistLevel));
        sn->score = score;
        return sn;
}

Skiplist *skiplistCreate() {
        Skiplist *sl;

        sl = malloc(sizeof(*sl));
        sl->level = 1;
        sl->length = 0;
        sl->header = slCreateNode(SKIPLIST_MAXLEVEL, 0);

        for (int j = 0; j < SKIPLIST_MAXLEVEL; j++) {
                sl->header->level[j].forward = NULL;
        }

        sl->header->backword = NULL;
        sl->tail = NULL;
        return sl;
}

bool skiplistSearch(Skiplist *obj, int target) {
        SkiplistNode *node;

        node = obj->header;
        for (int i = obj->level - 1; i >= 0; i--) {
                while (node->level[i].forward && node->level[i].forward->score < target) {
                        node = node->level[i].forward;
                }
        }
        node = node->level[0].forward;

        if (node && node->score == target) {
                return true;
        }
        return false;
}

void skiplistAdd(Skiplist *obj, int num) {
        SkiplistNode *update[SKIPLIST_MAXLEVEL];
        SkiplistNode *node;

        node = obj->header;
        for (int i = obj->level - 1; i >= 0; --i) {
                while (node->level[i].forward && node->level[i].forward->score < num) {
                        node = node->level[i].forward;
                }

                update[i] = node;
        }
        int level = slRandomLevel();
        if (level > obj->level) {
                // new level
                for (int i = obj->level; i < level; i++) {
                        update[i] = obj->header;
                }
                obj->level = level;
        }

        node = slCreateNode(level, num);
        for (int i = 0; i < level; i++) {
                node->level[i].forward = update[i]->level[i].forward;
                update[i]->level[i].forward = node;
        }

        node->backword = (update[0] == obj->header ? NULL : update[0]);

        if (node->level[0].forward) {
                node->level[0].forward->backword = node;
        } else {
                obj->tail = node;
        }
        obj->length++;
}

void slEraseNode(Skiplist *sl, SkiplistNode *node, SkiplistNode **update) {
        for (int i = 0; i < sl->level; i++) {
                if (update[i]->level[i].forward == node) {
                        update[i]->level[i].forward = node->level[i].forward;
                }
        }

        if (node->level[0].forward) {
                node->level[0].forward->backword = node->backword;
        } else {
                sl->tail = node->backword;
        }

        while (sl->level > 1 && sl->header->level[sl->level - 1].forward == NULL) {
                sl->level--;
        }

        sl->length--;
}

bool skiplistErase(Skiplist *obj, int num) {
        SkiplistNode *update[SKIPLIST_MAXLEVEL], *node;
        node = obj->header;

        for (int i = obj->level - 1; i >= 0; i--) {
                while (node->level[i].forward && node->level[i].forward->score < num) {
                        node = node->level[i].forward;
                }
                update[i] = node;
        }

        node = node->level[0].forward;

        if (node && num == node->score) {
                slEraseNode(obj, node, update);
                free(node);
                return true;
        }
        return false;
}

void skiplistFree(Skiplist *obj) {
        SkiplistNode *node = obj->header->level[0].forward, *next;
        free(obj->header);

        while (node) {
                next = node->level[0].forward;
                free(node);
                node = next;
        }
        free(obj);
}

/**
 * Your Skiplist struct will be instantiated and called as such:
 * Skiplist* obj = skiplistCreate();
 * bool param_1 = skiplistSearch(obj, target);

 * skiplistAdd(obj, num);

 * bool param_3 = skiplistErase(obj, num);

 * skiplistFree(obj);
*/

int main() {
        Skiplist *sl = skiplistCreate();
        skiplistAdd(sl, 11);
        skiplistAdd(sl, 12);
        skiplistErase(sl, 11);
        skiplistSearch(sl, 12);
        return 0;
}