#ifndef _BFS_
#define _BFS_
#include <limits.h>
#define MAXSIZE 100
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INFINITE INT_MAX

typedef struct gra_ptr_node {
  struct gra_ptr_node *next;
  struct graph_node *ptr;
} PTR_NODE;

typedef struct graph_node {
  struct graph_node *parent;
  struct graph_node *next;
  int key;
  int d;
  int f;
  int color;
} NODE;

typedef struct graph {
  PTR_NODE *adj[MAXSIZE];
  int length;
} GRAPH;

typedef struct stack_of_granode {
  NODE *arr_temp[MAXSIZE];
  int start;
  int end;
  int length;
  int count;
} NODEQUEUE;

NODE *arr_V[MAXSIZE];
void BFS(GRAPH *G, NODE *S);
void init_graph(GRAPH *G, int len);
void insert_to_adj(GRAPH *G, NODE *x, int key);
void init_queue(NODEQUEUE *Q, GRAPH *G);
NODE *create_and_init_node(int key);
NODE *dequeue(NODEQUEUE *Q);

#endif
