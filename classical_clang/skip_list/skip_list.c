/*
 * =====================================================================================
 *
 *       Filename:  skip_list.c
 *
 *    Description:  跳跃表简单实现
 *
 *        Version:  1.0
 *        Created:  2018-06-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAX_LEVEL 10

// 创建节点
nodeStructure *createNode(int level, int key, int value) {
        nodeStructure *ns = (nodeStructure *)malloc(
            sizeof(nodeStructure) + level * sizeof(nodeStructure *));
        ns->key = key;
        ns->value = value;
        return ns;
}

// 创建跳跃链
skiplist *createSkiplist() {
        skiplist *sl = (skiplist *)malloc(sizeof(skiplist));
        sl->level = 0;
        sl->header = createNode(MAX_LEVEL - 1, 0, 0);
        for (int i = 0; i < MAX_LEVEL; i++)
                sl->header->forward[i] = NULL;
        return sl;
}

// 产生随机层数量
int randomLevel() {
        int k = 1;
        while (rand() % 2)
                k++;
        k = (k < MAX_LEVEL) ? k : MAX_LEVEL;
        return k;
}

// 插入节点
int insert(skiplist *sl, int key, int value) {
        nodeStructure *update[MAX_LEVEL];
        nodeStructure *p, *q = NULL;

        p = sl->header;
        int k = sl->level;

        // 从最高层往下查找需要插入的位置
        for (int i = k - 1; i >= 0; i--) {
                while ((q = p->forward[i]) && (q->key < key))
                        p = q;
                update[i] = p;
        }

        // 不能插入相同的key
        if (q && q->key == key)
                return FALSE;

        // 产生一个随机的层
        k = randomLevel();
        // 新建一个待插入节点q 一层层的插入
        if (k > (sl->level)) {
                for (int i = sl->level; i < k; i++)
                        update[i] = sl->header;
                sl->level = k;
        }

        q = createNode(k, key, value);
        /* 逐层更新节点指针 */
        for (int i = 0; i < k; i++) {
                q->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = q;
        }
        return TRUE;
}

// 查找指定key
int search(skiplist *sl, int key) {
        nodeStructure *p, *q = NULL;
        p = sl->header;

        // 从最高层开始
        int k = sl->level;
        for (int i = k - 1; i >= 0; i--) {
                while ((q = p->forward[i]) && (q->key <= key)) {
                        if (q->key == key)
                                return q->value;
                        p = q;
                }
        }
        return 0;
}

int deleteSL(skiplist *sl, int key) {
        nodeStructure *update[MAX_LEVEL];
        nodeStructure *p, *q = NULL;
        p = sl->header;

        // 从最高层开始搜
        int k = sl->level;
        for (int i = k - 1; i >= 0; i--) {
                while ((q = p->forward[i]) && (q->key <= key))
                        p = q;
                update[i] = p;
        }
        if (q && q->key == key) {
                for (int i = 0; i < sl->level; i++) {
                        if (update[i]->forward[i] == q)
                                update[i]->forward[i] = q->forward[i];
                }
                free(q);
                // 如果删除的是最大层的节点，需要重新维护跳跃表
                for (int i = sl->level - 1; i >= 0; i--) {
                        if (sl->header->forward[i] == NULL)
                                sl->level--;
                }
                return TRUE;
        } else {
                return FALSE;
        }
}

void printSL(skiplist *sl) {
        nodeStructure *p, *q = NULL;
        int k = sl->level;
        for (int i = k - 1; i >= 0; i--) {
                p = sl->header;
                while ((q = p->forward[i])) {
                        printf("%d -> ", p->value);
                        p = q;
                }
                printf("%d", p->value);
                printf("\n");
        }
        printf("\n");
}

int main() {
        skiplist *sl = createSkiplist();
        for (int i = 0; i < 19; i++)
                insert(sl, i, i * i);
        printSL(sl);

        int i = search(sl, 18);
        printf("i=%d\n", i);

        // 删除
        int b = deleteSL(sl, 4);
        if (b > 0)
                printf("删除成功\n");
        printSL(sl);
        /* system("pause"); */
        return 0;
}
