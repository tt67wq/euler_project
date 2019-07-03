/*
 * =====================================================================================
 *
 *       Filename:  heap_sort.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-07-02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef kvec_t(int) heap;

void init(heap *pq) { kv_init(*pq); }
void destroy(heap *pq) { kv_destroy(*pq); }

void insert(int x, heap *pq) { kv_push(int, *pq, x); }

// 堆调整
void fix_heap(int pos, heap *pq) {
        // 将当前位置的数字下沉
        int tmp = kv_A(*pq, pos); // 取出当前元素
        for (int k = 2 * pos + 1; k < kv_size(*pq); k = 2 * k + 1) {
                // 从i的左节点开始
                if (k + 1 < kv_size(*pq) && (kv_A(*pq, k) < kv_A(*pq, k + 1))) {
                        // 如果左节点小于右节点 选右节点
                        k += 1;
                }
                if (kv_A(*pq, k) > tmp) {
                        // 如果节点大于父节点 将字节点的值赋值给父节点
			// 这里实现的是大顶堆，小顶堆就反过来
                        pq->a[pos] = kv_A(*pq, k);
                        pos = k;
                } else {
                        break;
                }
        }
        // 将tmp放入最终的位置
        pq->a[pos] = tmp;
}

// 排序
void sort(heap *pq) {
        // 构建大顶堆
        for (int i = kv_size(*pq) / 2 - 1; i >= 0; i--) {
                // 从第一个非叶子节点开始，从下至上，从右至左 将数字下沉到合适位置
                fix_heap(i, pq);
        }

        // 将堆顶元素与堆尾部交换
        for (int j = kv_size(*pq) - 1; j > 0; j--) {
                // swap pq[0] and pq[j]
                int tmp = kv_A(*pq, j);
                pq->a[j] = pq->a[0];
                pq->a[0] = tmp;

                // rebuild heap
                fix_heap(0, pq);
        }
}

int main(int argc, const char *argv[]) {
        heap h;
        init(&h);
        int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

        for (int i = 0; i < 9; i++)
                insert(arr[i], &h);

        sort(&h);

        for (int i = 0; i < kv_size(h); i++)
                printf("%d ", kv_A(h, i));

        printf("\n");
        return 0;
}
