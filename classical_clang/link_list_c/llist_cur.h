/* ifndef _Cursor_H */
typedef int ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void initializeCursorSpace(void);

List MakeEmpty(List L);
int IsEmpty(const List);
int IsLast(const Position P, const List L);
Position Find(ElementType X, const List L);
void Delete(ElementType X, const List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
/* endif */

struct Node {
        ElementType Element;
        Position Next;
};

struct Node CursorSpace[10];
