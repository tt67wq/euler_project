#ifndef _DisjoinSet_
#define _DisjoinSet_

typedef int Item;
typedef Item SetType;
typedef SetType *DisjoinSet;

/* 接口函数声明 */

/*  操作: 按高度初始化一个不相交集和   */
/*  操作前:    gather 是一个不相交集合, size 是指示不相交集合的大小   */
/*  操作后:    除将第一个集合数据域设置为集合的实际大小外,
 * 将所有集合数据域被初始化为HEIGHT  */
void InitializeAsHeight(DisjiontSet gather, const int size);

/*  操作: 按大小初始化一个不相交集合   */
/*  操作前:    gather 是一个不相交集合, size 指示不相交集合的大小    */
/*  操作后:    除将第一个集合数据域位置为集合的实际大小外,
 * 所有集合数据域被初始化为SIZE */
void InitializeAsSize(DisjoinSet gather, const int size);

/*  操作: 按树的高度求并两个集合 */
/*  操作前:    gather 是一个已初始化的不相交集合, root1, root2
 * 是两个集合类型的变量   */
/*  操作后:    如果集合类型在 gather 中, 按高度求并 root1 集合和 root2 集合,
 * 返回1; 否则返回0  */
int SetUnionAsHeight(DisjoinSet gather, SetType root1, SetType root2);

/*  操作: 按树的大小求并两个集合 */
/*  操作前:    gather 是一个已初始化的不相交集合, root1, root2
 * 是两个集合类型的变量   */
/*  操作后:    如果集合类型在 gather 中, 按大小求并 root1 集合和 root2 集合,
 * 返回1; 否则返回0  */
int SetUnionAsSize(DisjoinSet gather, SetType root1, SetType root2);

/*  操作: 根据一个不相交集合和一个数据, 查找并返回该数据所在集合类型,
 * 并进行路径压缩 */
/*  操作前:    gather 是一个已初始化的不相交集合, item 是一个Item类型变量  */
/*  操作后:    如果 item 所在集合在 gather 中, 找到并返回 item 所在集合的类型,
 * 并进行路径压缩; 否则返回 OOS   */
SetType Find(DisjoinSet gather, const Item item);

#endif
