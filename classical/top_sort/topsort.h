#ifndef _TopSort_
#define _TopSort_

typedef struct _ENode {
        int ivex;
        struct _ENode *next_edge;
} ENode, *PENode;

typedef struct _VNode {
        char data;
        PENode first_edge;
} VNode, *PrToVNode;

typedef struct _LGraph {
        int vexnum;
        int edgnum;
        PrToVNode *vexs;
} LGraph, *PrToLGraph;

int toplogical_sort(PrToLGraph G);

#endif
