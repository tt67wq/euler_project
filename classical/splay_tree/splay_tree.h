typedef int ElementType;
struct SplayTreeNode;
typedef struct SplayTreeNode *SplayTree;
typedef struct SplayTreeNode *Position;
struct SplayTreeNode {
  ElementType Element;
  SplayTree Left;
  SplayTree Right;
};

SplayTree MakeEmpty(SplayTree T);             /* 初始化 */
void PreorderSplayTree(SplayTree T);          /* 前序遍历 */
void InorderSplayTree(SplayTree T);           /* 中序遍历 */
void PostorderSplayTree(SplayTree T);         /* 后序遍历 */
Position Find(ElementType X, SplayTree T);    /* 搜索 */
Position FindMin(SplayTree T);                /* 寻找最小值 */
Position FindMax(SplayTree T);                /* 寻找最大值 */
SplayTree Insert(ElementType X, SplayTree T); /* 插入元素 */
SplayTree Delete(ElementType X, SplayTree T); /* 删除元素 */
