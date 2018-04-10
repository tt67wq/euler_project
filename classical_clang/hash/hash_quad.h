/* hash开放定址法实现 */
typedef unsigned int Index;
typedef Index Position;
typedef int ElementType;

struct HashTbl;
typedef struct HashTbl *HashTable;

#define MinTableSize 10

HashTable Initialize(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType X, HashTable H);
void Insert(ElementType X, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);

enum KindOfEntry { Legitimate, Empty, Deleted };

struct HashEntry {
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl {
	int TableSize;
	Cell *TheCells;
};
