#include "llist_cur.h"
#include <stdio.h>
#include <stdlib.h>

static Position CursorAlloc(void) {
  Position P;
  P = CursorSpace[0].Next;
  CursorSpace[0].Next = CursorSpace[P].Next;
  return P;
}

static void CursorFree(Position P) {
  CursorSpace[P].Next = CursorSpace[0].Next;
  CursorSpace[0].Next = P;
}
