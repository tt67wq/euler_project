/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define MAX_SIZE 10000

static int m_heap[MAX_SIZE];
static int m_capacity = MAX_SIZE; // 总的容量
static int m_size = 0;            // 实际容量(初始化为0)

/*
 * 最小堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void minheap_filterdown(int start, int end) {
        int c = start;       // 当前(current)节点的位置
        int l = 2 * c + 1;   // 左(left)孩子的位置
        int tmp = m_heap[c]; // 当前(current)节点的大小

        while (l <= end) {
                // "l"是左孩子，"l+1"是右孩子
                if (l < end && m_heap[l] > m_heap[l + 1])
                        l++; // 左右两孩子中选择较小者，即m_heap[l+1]
                if (tmp <= m_heap[l])
                        break; //调整结束
                else {
                        m_heap[c] = m_heap[l];
                        c = l;
                        l = 2 * l + 1;
                }
        }
        m_heap[c] = tmp;
}

/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
static void filter_up(int start) {
        int c = start;       // 当前节点(current)的位置
        int p = (c - 1) / 2; // 父(parent)结点的位置
        int tmp = m_heap[c]; // 当前节点(current)的大小

        while (c > 0) {
                if (m_heap[p] <= tmp)
                        break;
                else {
                        m_heap[c] = m_heap[p];
                        c = p;
                        p = (p - 1) / 2;
                }
        }
        m_heap[c] = tmp;
}

/*
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int minheap_insert(int data) {
        // 如果"堆"已满，则返回
        if (m_size == m_capacity)
                return -1;

        m_heap[m_size] = data; // 将"数组"插在表尾
        filter_up(m_size);     // 向上调整堆
        m_size++;              // 堆的实际容量+1

        return 0;
}

int findKthLargest(int *nums, int numsSize, int k) {
        int i;

        // init heap
        bzero(m_heap, sizeof(int) * m_capacity);
        m_size = 0;

        for (i = 0; i < numsSize; i++) {

                if (m_size < k) {
                        minheap_insert(nums[i]);
                } else {
                        if (nums[i] > m_heap[0]) {
                                m_heap[0] = nums[i];
				minheap_filterdown(0, m_size - 1);
                        } 
                }
        }

        return m_heap[0];
}

int main() {
        int nums[7] = {7, 6, 5, 4, 3, 2, 1};
        printf("%d\n", findKthLargest(nums, 7, 4));
        return 0;
}
