/* avl树声明 */
struct AvlNode;
typedef int ElementType;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty(AvlTree T);
int GetHeight(AvlTree T); //得到树的高度
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
void InorderTraversal(AvlTree T);    //递归中序遍历
void PreorderTraversal(AvlTree T);   //递归前序遍历树
void PostorderTraversal(AvlTree T);  //递归后序遍历
void GetOrderPrintLeaves(AvlTree T); //递归求叶子节点

struct AvlNode {
  ElementType Element;
  AvlTree Left;
  AvlTree Right;
  int Height;
};
