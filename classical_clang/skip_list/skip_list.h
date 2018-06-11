#ifndef __SkipList__
#define __SkipList__

// 节点
typedef struct nodeStructure {
        int key;
        int value;
        struct nodeStructure *forward[1];
} nodeStructure;

// 跳表
typedef struct skiplist {
        int level;
        nodeStructure *header;
} skiplist;

#endif
