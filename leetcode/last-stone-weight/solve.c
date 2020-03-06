/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

static int m_heap[30];      // 数据
static int m_capacity = 30; // 总的容量
static int m_size = 0;      // 实际容量(初始化为0)

/*
 * 返回data在二叉堆中的索引
 *
 * 返回值：
 *     存在 -- 返回data在数组中的索引
 *     不存在 -- -1
 */
int get_index(int data) {
        int i = 0;

        for (i = 0; i < m_size; i++)
                if (data == m_heap[i])
                        return i;

        return -1;
}

/*
 * 最大堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void maxheap_filterdown(int start, int end) {
        int c = start;       // 当前(current)节点的位置
        int l = 2 * c + 1;   // 左(left)孩子的位置
        int tmp = m_heap[c]; // 当前(current)节点的大小

        while (l <= end) {
                // "l"是左孩子，"l+1"是右孩子
                if (l < end && m_heap[l] < m_heap[l + 1])
                        l++; // 左右两孩子中选择较大者，即m_heap[l+1]
                if (tmp >= m_heap[l])
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
 * 删除最大堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int maxheap_remove(int data) {
        int index;
        // 如果"堆"已空，则返回-1
        if (m_size == 0)
                return -1;

        // 获取data在数组中的索引
        index = get_index(data);
        if (index == -1)
                return -1;

        m_heap[index] = m_heap[--m_size];      // 用最后元素填补
        maxheap_filterdown(index, m_size - 1); // 从index位置开始自上向下调整为最大堆

        return 0;
}

/*
 * 弹出堆头
 */
int maxheap_pop() {
        int data;
        // 如果"堆"已空，则返回-1
        if (m_size == 0)
                return -1;

        data = m_heap[0];
        m_heap[0] = m_heap[--m_size];
        maxheap_filterdown(0, m_size - 1); // 从index位置开始自上向下调整为最大堆

        return data;
}

/*
 * 最大堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
static void maxheap_filterup(int start) {
        int c = start;       // 当前节点(current)的位置
        int p = (c - 1) / 2; // 父(parent)结点的位置
        int tmp = m_heap[c]; // 当前节点(current)的大小

        while (c > 0) {
                if (m_heap[p] >= tmp)
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
int maxheap_insert(int data) {
        // 如果"堆"已满，则返回
        if (m_size == m_capacity)
                return -1;

        m_heap[m_size] = data;    // 将"数组"插在表尾
        maxheap_filterup(m_size); // 向上调整堆
        m_size++;                 // 堆的实际容量+1

        return 0;
}

int lastStoneWeight(int *stones, int stonesSize) {
        int i, x, y;

        for (i = 0; i < stonesSize; i++) {
                maxheap_insert(stones[i]);
        }

        while (m_size > 1) {
                y = maxheap_pop();
                x = maxheap_pop();
                if (x == y) {
                        // pass
                } else {
                        maxheap_insert(y - x);
                }
        }
        if (m_size == 1)
                return maxheap_pop();
        return 0;
}

int main() {}
