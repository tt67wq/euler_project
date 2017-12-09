typedef struct TreeNode *PtrToNode;

typedef int ElementType;

struct TreeNode {
  ElementType Element;
  PtrToNode FirstChild;
  PtrToNode NextSibling;
}
