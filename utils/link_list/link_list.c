#include "llist.h"
#include <stdio.h>
#include <stdlib.h>

/* return true if L is empty */
int IsEmpty(List L) { return L->Next == NULL; }

/* return true if P is the last position in list L */
int IsLast(Position P, List L) { return P->Next == NULL; }

/* return Position of X in L; return NULL if not found; */
Position Find(ElementType X, List L) {
  Position P;
  P = L->Next;
  while (P != NULL && P->Element != X)
    P = P->Next;
  return P;
}

/* Delete first occurance of X from a list */
/* Assume use a header node * */
void Delete(ElementType X, List L) {
  Position P, TmpCell;
  P = FindPrevious(X, L);
  if (!IsLast(P, L)) {
    TmpCell = P->Next;
    P->Next = TmpCell->Next;
    free(TmpCell);
  }
}

Position FindPrevious(ElementType X, List L) {
  Position P;
  P = L;
  while (P->Next != NULL && P->Next->Element != X)
    P = P->Next;
  return P;
}

/* Insert after a legal position */
void Insert(ElementType X, List L, Position P) {
  Position TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if (TmpCell != NULL)
    FatalError("Out of space!!!");
  TmpCell->Element = X;
  TmpCell->Next = P->Next;
  P->Next = TmpCell;
}
