/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-07-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <uthash.h>

// 创建一个基于时间的键值存储类 TimeMap，它支持下面两个操作：

// 1. set(string key, string value, int timestamp)

// 存储键 key、值 value，以及给定的时间戳 timestamp。
// 2. get(string key, int timestamp)

// 返回先前调用 set(key, value, timestamp_prev) 所存储的值，其中 timestamp_prev <= timestamp。
// 如果有多个这样的值，则返回对应最大的  timestamp_prev 的那个值。
// 如果没有值，则返回空字符串（""）。
//  

// 示例 1：

// 输入：inputs = ["TimeMap","set","get","get","set","get","get"], inputs =
// [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
// 输出：[null,null,"bar","bar",null,"bar2","bar2"]
// 解释： 
// TimeMap kv;  
// kv.set("foo", "bar", 1); // 存储键 "foo" 和值 "bar" 以及时间戳 timestamp = 1  
// kv.get("foo", 1);  // 输出 "bar"  
// kv.get("foo", 3); // 输出 "bar" 因为在时间戳 3 和时间戳 2 处没有对应 "foo"
// 的值，所以唯一的值位于时间戳 1 处（即 "bar"）   kv.set("foo", "bar2", 4);   kv.get("foo", 4); //
// 输出 "bar2"   kv.get("foo", 5); // 输出 "bar2"  

// 示例 2：

// 输入：inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs =
// [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
// 输出：[null,null,null,"","high","high","low","low"]
//  

// 提示：

// 所有的键/值字符串都是小写的。
// 所有的键/值字符串长度都在 [1, 100] 范围内。
// 所有 TimeMap.set 操作中的时间戳 timestamps 都是严格递增的。
// 1 <= timestamp <= 10^7
// TimeMap.set 和 TimeMap.get 函数在每个测试用例中将（组合）调用总计 120000 次。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/time-based-key-value-store
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
#define MAX 100

struct entry {
        char *value;
        int timestmap;
        LIST_ENTRY(entry) next;
};

LIST_HEAD(lhead, entry);

struct table {
        char *key;
        struct lhead *h;
        int entriesSize;
        UT_hash_handle hh;
};

typedef struct {
        struct table *tsTable;
} TimeMap;

/** Initialize your data structure here. */

TimeMap *timeMapCreate() {
        TimeMap *tm = (TimeMap *)malloc(sizeof(TimeMap));
        tm->tsTable = NULL;
        return tm;
}

void timeMapSet(TimeMap *obj, char *key, char *value, int timestamp) {
        struct table *s = NULL;
        HASH_FIND_STR(obj->tsTable, key, s);
        if (!s) {
                s = (struct table *)malloc(sizeof(struct table));
                s->key = (char *)calloc(MAX, sizeof(char));
                s->h = (struct lhead *)malloc(sizeof(struct lhead));
                LIST_INIT(s->h);
                s->entriesSize = 0;
                strcpy(s->key, key);
                HASH_ADD_STR(obj->tsTable, key, s);
        }
        struct entry *_en = (struct entry *)malloc(sizeof(struct entry));
        _en->timestmap = timestamp;
        _en->value = (char *)calloc(MAX, sizeof(char));
        strcpy(_en->value, value);
        LIST_INSERT_HEAD(s->h, _en, next);
        s->entriesSize++;
}

char *timeMapGet(TimeMap *obj, char *key, int timestamp) {
        struct table *s = NULL;
        HASH_FIND_STR(obj->tsTable, key, s);
        if (s) {
                struct entry *en;
                LIST_FOREACH(en, s->h, next) {
                        if (en->timestmap <= timestamp) {
                                return en->value;
                        }
                }
        }
        return "";
}

void timeMapFree(TimeMap *obj) {
        struct table *iter, *tmp;
        struct entry *s;
        HASH_ITER(hh, obj->tsTable, iter, tmp) {
                while (!LIST_EMPTY(iter->h)) {
                        s = LIST_FIRST(iter->h);
                        LIST_REMOVE(s, next);
                        free(s->value);
                        free(s);
                }
                free(iter->key);
                free(iter);
        }
        free(obj);
}

/**
 * Your TimeMap struct will be instantiated and called as such:
 * TimeMap* obj = timeMapCreate();
 * timeMapSet(obj, key, value, timestamp);

 * char * param_2 = timeMapGet(obj, key, timestamp);

 * timeMapFree(obj);
*/

int main() {
        // ["TimeMap","set","set","get","get","get","get","get"]
        // [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
        TimeMap *tm = timeMapCreate();
        timeMapSet(tm, "love", "high", 10);
        timeMapSet(tm, "love", "low", 20);

        char *ans;
        ans = timeMapGet(tm, "love", 5);
        printf("%s\n", ans);

        ans = timeMapGet(tm, "love", 10);
        printf("%s\n", ans);

        ans = timeMapGet(tm, "love", 20);
        printf("%s\n", ans);

        ans = timeMapGet(tm, "love", 25);
        printf("%s\n", ans);

        timeMapFree(tm);
        return 0;
}