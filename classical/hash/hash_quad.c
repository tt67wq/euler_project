#include "hash_quad.h"
#include <stdio.h>
#include <stdlib.h>

HashTable Initialize(int TableSize) {
  HashTable H;
  int i;

  if (TableSize < MinTableSize) {
    printf("Table size too small\n");
    return NULL;
  }

  /* allocate table */
  H = malloc(sizeof(struct HashTbl));
  if (!H) {
    printf("malloc error\n");
    exit(EXIT_FAILURE);
  }

  /* allocate array */
  H->TableSize = NextPrime(TableSize);
  H->TheCells = malloc(sizeof(Cell) * H->TableSize);
  if (H->TheCells == NULL) {
    printf("out of space\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < H->TableSize; i++)
    H->TheCells[i].Info = Empty;
  return H;
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

Position Find(ElementType X, HashTable H) {
  Position CurrentPos;
  int CollisionNum;

  CollisionNum = 0;
  CurrentPos = Hash(X, H->TableSize);
  while (H->TheCells[CurrentPos].Info != Empty &&
         H->TheCells[CurrentPos].Element != X) {
    CurrentPos += 2 * ++CollisionNum - 1;
    if (CurrentPos >= H->TableSize)
      CurrentPos -= H->TableSize;
  }
  return CurrentPos;
}

void Insert(ElementType X, HashTable H) {
  Position Pos;
  Pos = Find(X, H);
  if (H->TheCells[Pos].Info != Legitimate) {
    /* ok to insert here */
    H->TheCells[Pos].Info = Legitimate;
    H->TheCells[Pos].Element = X;
  }
}

HashTable Rehash(HashTable H) {
  int i, OldSize;
  Cell *OldCells;

  OldCells = H->TheCells;
  OldSize = H->TableSize;

  /* get a new,empty table */
  H = Initialize(2 * OldSize);

  /* scan through old table, reinserting into new */
  for (i = 0; i < OldSize; i++)
    if (OldCells[i].Info == Legitimate)
      Insert(OldCells[i].Element, H);
  free(OldCells);
  return H;
}
