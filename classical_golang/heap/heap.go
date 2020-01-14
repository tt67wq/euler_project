package main

// 最大堆实现
import (
	"fmt"
)

type heap struct {
	size     int
	capacity int
	data     []int
}

func (h *heap) get_index(data int) int {
	var i int

	for i = 0; i < h.size; i++ {
		if data == h.data[i] {
			return i
		}
	}
	return -1
}

func new_heap(capacity int) *heap {
	var h *heap
	h = new(heap)
	h.capacity = capacity
	h.size = 0
	h.data = make([]int, capacity)
	return h
}

// 最大堆向下调整
func (h *heap) maxheap_filterdown(start, end int) {
	var c, l, t int

	c = start     // current
	l = 2*c + 1   // 左子
	t = h.data[c] // current值

	for l <= end {
		// 若左子右子中较大的
		if l < end && h.data[l] < h.data[l+1] {
			l++
		}
		// 位置合适，结束
		if t >= h.data[l] {
			break
		} else {
			// 下降 当前节点与子节点互换
			h.data[c] = h.data[l] // 上移
			c = l                 // 节点目前位置
			l = l*2 + 1           // 下个左子
		}
	}
	h.data[c] = t
}

// 最大堆向上调整
func (h *heap) maxheap_filterup(start int) {
	var c, p, t int

	c = start       // current
	p = (c - 1) / 2 // parent
	t = h.data[start]

	for c > 0 {
		if h.data[p] > t {
			break
		} else {
			// 父比子小 父子互换
			h.data[c] = h.data[p]
			c = p
			p = (p - 1) / 2
		}
	}
	h.data[c] = t
}

// 插入
func (h *heap) maxheap_insert(data int) bool {
	if h.capacity == h.size {
		return false
	}

	h.data[h.size] = data      // 插在堆尾
	h.maxheap_filterup(h.size) // 向上调整
	h.size++

	return true
}

// 删除
func (h *heap) maxheap_remove(data int) bool {
	if h.size == 0 {
		return false
	}
	var index int
	index = h.get_index(data)
	if index == -1 {
		return false
	}
	h.data[index] = h.data[h.size-1] // 堆尾填充空缺
	h.size--
	h.maxheap_filterdown(index, h.size-1)
	return true
}

// 弹出堆头
func (h *heap) pop_head() int {
	var r int
	r = h.data[0]
	h.data[0] = h.data[h.size-1] // 堆尾填充空缺
	h.size--
	h.maxheap_filterdown(0, h.size-1)
	return r
}

func (h *heap) view_heap() {
	var i int

	for i = 0; i < h.size; i++ {
		fmt.Print(h.data[i], " ")
	}
	fmt.Print("\n")
}

func main() {
	var nums []int
	var h *heap

	nums = []int{10, 40, 30, 60, 90, 70, 20, 50, 80}
	h = new_heap(30)

	for _, num := range nums {
		h.maxheap_insert(num)
	}

	for h.size > 0 {
		fmt.Println(h.pop_head())
	}
}
