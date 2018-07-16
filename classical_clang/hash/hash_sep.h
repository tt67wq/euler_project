/* 分离链接法hash */
struct ListNode;
typedef int ElementType;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef Position List;

#define MinTableSize 10
#define TRUE 1;
#define FALSE 0;

HashTable Initialize(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType X, HashTable H);
void Insert(ElementType X, HashTable H);
int Delete(ElementType X, HashTable H);
ElementType Retrieve(Position P);
int Hash(ElementType X, int TableSize);

struct ListNode {
        ElementType Element;
        Position Next;
};

struct HashTbl {
        int TableSize;
        List *TheLists;
}
