/* ifndef _Tree_H */
struct TreeNode;
typedef int ElementType;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int (*CmpFunc)(int, int);

void MakeEmpty(SearchTree T);
SearchTree CreateTree();
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
void Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);
int Compare(ElementType X, ElementType Y);
/* endif _Tree_H */

struct TreeNode {
  ElementType Element;
  SearchTree Left;
  SearchTree Right;
  CmpFunc Compare;
};
