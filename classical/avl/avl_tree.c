#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

static int Height(Position P) {
        if (P == NULL)
                return -1;
        return P->Height;
}

AvlTree MakeEmpty(AvlTree T) {
        if (T == NULL) {
                T = malloc(sizeof(struct AvlNode));
                if (T == NULL) {
                        printf("malloc error\n");
                        exit(EXIT_FAILURE);
                }
        }
        T->Height = 0;
        T->Left = NULL;
        T->Right = NULL;
        T->Element = 0;
        return T;
}

int isEmpty(AvlTree T) {
        if (!T)
                return 1;
        else
                return 0;
}

int GetHeight(AvlTree T) {
        int AL, AR, MAX;
        while (T) {
                AL = GetHeight(T->Left);
                AR = GetHeight(T->Right);
                MAX = (AL > AR) ? AL : AR;
                return MAX + 1;
        }
        return 0;
}

Position Find(ElementType X, AvlTree T) {
        if (T == NULL)
                return NULL;
        if (X < T->Element)
                return Find(X, T->Left);
        else if (X > T->Element)
                return Find(X, T->Right);
        else
                return T;
}

Position FindMin(AvlTree T) {
        if (T == NULL)
                return NULL;
        else if (T->Left == NULL)
                return T;
        return FindMin(T->Left);
}

Position FindMax(AvlTree T) {
        if (T == NULL)
                return NULL;
        else if (T->Right == NULL)
                return T;
        return FindMax(T->Right);
}

void InorderTraversal(AvlTree T) {
        if (T) {
                InorderTraversal(T->Left);
                printf("%d\n", T->Element);
                InorderTraversal(T->Right);
        }
}

void PreorderTraversal(AvlTree T) {
        if (T) {
                printf("%d\n", T->Element);
                PreorderTraversal(T->Left);
                PreorderTraversal(T->Right);
        }
}

void PostorderTraversal(AvlTree T) {
        if (T) {
                PostorderTraversal(T->Left);
                PostorderTraversal(T->Right);
                printf("%d\n", T->Element);
        }
}

void GetOrderPrintLeaves(AvlTree T) {
        if (T) {
                if (T->Left || T->Right) {
                        GetOrderPrintLeaves(T->Left);
                        GetOrderPrintLeaves(T->Right);
                }
                printf("%d\n", T->Element);
        }
}

int max(int a, int b) { return (a > b) ? a : b; }

// LL型平衡调整，又称单向右旋平衡处理
AvlTree singleLeftRotation(AvlTree T) {
        /* 必须有个左子树 */
        AvlTree LT = T->Left;
        T->Left = LT->Right;
        LT->Right = T;
        T->Height = max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
        LT->Height = max(GetHeight(T->Left), GetHeight(LT->Right)) + 1;

        return LT;
}

// RR型平衡调整，又称单向左旋平衡处理
AvlTree singleRightRotation(AvlTree T) {
        /* 必须要右子树 */
        AvlTree RT;
        RT = T->Right;
        T->Right = RT->Left;
        RT->Left = T;
        T->Height = max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
        RT->Height = max(GetHeight(T->Right), GetHeight(RT->Left)) + 1;

        return RT;
}

// LR型平衡调整，又称双向旋转（先左后右）平衡处理
AvlTree doubleLeftRightRotation(AvlTree T) {
        T->Left = singleRightRotation(T->Left);
        return singleLeftRotation(T);
}

// RL型平衡调整，又称双向旋转（向右后左）平衡处理
AvlTree doubleRightLeftRotation(AvlTree T) {
        T->Right = singleLeftRotation(T->Right);
        return singleRightRotation(T);
}

AvlTree Insert(ElementType X, AvlTree T) {
        if (isEmpty(T)) {
                T = MakeEmpty(T);
                T->Element = X;
                T->Height = 0;
                T->Left = T->Right = NULL;
        } else if (X < T->Element) {
                /* printf("插入左边\n"); */
                T->Left = Insert(X, T->Left);
                if (GetHeight(T->Left) - GetHeight(T->Right) == 2) /* 如果需要左旋 */
                        if (X < T->Left->Element)
                                T = singleLeftRotation(T);
                        else
                                T = doubleLeftRightRotation(T);
        } else if (X > T->Element) {
                /* printf("插入右边\n"); */
                T->Right = Insert(X, T->Right);
                if (GetHeight(T->Right) - GetHeight(T->Left) == 2)
                        if (X > T->Right->Element)
                                T = singleRightRotation(T);
                        else
                                T = doubleRightLeftRotation(T);
        } else {
                // 已经在树中
        }
        T->Height = max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
        return T;
}

AvlTree Delete(ElementType X, AvlTree T) {
        if (isEmpty(T)) {
                printf("empty tree\n");
                return T;
        }
        if (X < T->Element) {
                // 待删除的节点在左子树中
                T->Left = Delete(X, T->Left);
                if (GetHeight(T->Right) - GetHeight(T->Left) == 2) {
                        /* 失去平衡 */
                        if (GetHeight(T->Right->Left) > GetHeight(T->Right->Right))
                                T = doubleRightLeftRotation(T);
                        else
                                T = singleRightRotation(T);
                }
                // 未失衡
        } else if (X > T->Element) {
                // 待删除的节点在右子树中
                T->Right = Delete(X, T->Right);
                if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
                        /* 失去平衡 */
                        if (GetHeight(T->Left->Left) < GetHeight(T->Left->Right))
                                T = doubleLeftRightRotation(T);
                        else
                                T = singleLeftRotation(T);
                }
                /* 未失衡 */
        } else {
                // 该节点为待删除的点
                if (T->Left && T->Right) {
                        //左右子树都非空
                        if (GetHeight(T->Left) > GetHeight(T->Right)) {
                                /* 左子树比右子树高 */
                                /* 找出左子树中的最大节点，将最大节点的值赋给T，删除该最大节点 */
                                Position P;
                                P = FindMax(T->Left);
                                T->Element = P->Element;
                                T->Left = Delete(P->Element, T->Left);
                        } else {
                                /* 左子树不比右子树高 */
                                /* 找出右子树中的最小节点，将最小节点的值赋给T，删除该最小节点 */
                                Position P;
                                P = FindMin(T->Right);
                                T->Element = P->Element;
                                T->Right = Delete(P->Element, T->Right);
                        }
                } else {
                        //有一个子树为空AvlTree Tmp = T;
                        T = T->Left ? T->Left : T->Right;
                        free(Tmp);
                }
        }
        return T;
}

int main() {
        static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
        AvlTree T;
        int i, l;

        T = MakeEmpty(T);
        l = TBL_SIZE(arr);

        for (i = 0; i < l; i++) {
                printf("插入元素%d\n", arr[i]);
                T = Insert(arr[i], T);
        }
        printf("中序遍历: ----------------------------- \n");
        InorderTraversal(T);
        printf("前序遍历: ----------------------------- \n");
        PreorderTraversal(T);
        printf("后序遍历: ----------------------------- \n");
        PostorderTraversal(T);
        printf("叶子递归: ----------------------------- \n");
        GetOrderPrintLeaves(T);
        exit(EXIT_SUCCESS);
}
