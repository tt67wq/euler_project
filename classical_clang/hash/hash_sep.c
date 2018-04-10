#include "hash_sep.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

HashTable Initialize(int TableSize) {
  HashTable H;
  int i;

  if (TableSize < MinTableSize) {
    printf("tablesize too small\n");
    exit(EXIT_FAILURE);
  }
  H = malloc(sizeof(struct HashTbl));
  if (!H) {
    printf("malloc error\n");
    exit(EXIT_FAILURE);
  }
  H->TableSize = NextPrime(TableSize);
  H->TheLists = malloc(sizeof(List) * H->TableSize);
  if (H->TheLists == NULL) {
    printf("malloc error\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < H->TableSize; i++) {
    H->TheLists[i] = malloc(sizeof(struct ListNode));
    if (H->TheLists[i] == NULL) {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    } else {
      H->TheLists[i]->Next = NULL;
    }
  }
  return H;
}

void DestroyTable(HashTable H) {
  int i;
  position h, p, q;
  for (i = 0; i < H->TableSize; i++) {
    h = H->TheLists[i];
    p = h->Next;
    while (p) {
      q = p->Next;
      if (!q) {
        free(p);
        p = NULL;
      } else {
        free(p);
        q = p;
      }
    }
  }
}

int isPrime(int Num) {
  int i;
  int flag = FALSE;

  for (i = 2; i <= Num / 2; ++i) {
    // 符合该条件不是素数
    if (Num % i == 0) {
      flag = TRUE;
      break;
    }
  }
  return flag;
}

int NextPrime(int Num) {
  if (Num == 2)
    return 3;
  else {
    Num += 2;
    while (!isPrime(Num)) {
      Num += 2;
    }
    return Num;
  }
}

int Hash(ElementType X, int TableSize) { return X % TableSize; }

Position Find(ElementType X, HashTable H) {
  Position P;
  List L;

  L = H->TheLists[Hash(X, H->TableSize)];
  P = L->Next;
  while (P != NULL && P->Element != X)
    P = P->Next;
  return P;
}

void Insert(ElementType X, HashTable H) {
  Position P, NewCell;
  List L;
  P = Find(X, H);
  if (!P) {
    NewCell = malloc(sizeof(struct ListNode));
    if (NewCell == NULL) {
      printf("malloc error\n");
      exit(EXIT_FAILURE);
    } else {
      L = H->TheLists[Hash(X, H->TableSize)];
      NewCell->Next = L->Next;
      NewCell->Element = X;
      L->Next = NewCell;
    }
  }
}

int Delete(ElementType X, HashTable H) {
  Position pos, h, L;
  L = H->TheLists[Hash(X, H->TableSize)];
  h = L->Next;
  while (h != NULL && h->Next && h->Next->Element != X)
    pos = pos->Next;
  if (h == NULL) {
    printf("cannot find that key!");
    return FALSE;
  } else {
    pos = h->Next;
    h->Next = pos->Next;
    free(pos);
    return TRUE;
  }
}
