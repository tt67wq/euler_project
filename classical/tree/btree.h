/* 二叉树声明 */
typedef int ElementType;
typedef struct TreeNode *PtrToNode;
typedef struct PtrToNode Tree;

struct TreeNode {
  ElementType Element;
  Tree Left;
  Tree Right;
}
