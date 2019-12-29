package main

import (
	"fmt"
)

func relativeSortArray(arr1 []int, arr2 []int) []int {

	var index map[int]int = make(map[int]int)
	var p1, p2 []int = make([]int, 0), make([]int, 0)

	// build idx
	for i, hwf := range arr2 {
		index[hwf] = i
	}

	for _, b1z := range arr1 {
		if _, ok := index[b1z]; ok {
			p1 = append(p1, b1z)
		} else {
			p2 = append(p2, b1z)
		}
	}

	quick_sort_by_index(p1, 0, len(p1)-1, index)
	quick_sort(p2, 0, len(p2)-1)

	return append(p1, p2...)
}

func quick_sort(nums []int, begin, end int) {
	var i, j, t int

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if nums[i] > nums[begin] {
				// swap
				t = nums[i]
				nums[i] = nums[j]
				nums[j] = t
				j--
			} else {
				i++
			}
		}

		if nums[i] >= nums[begin] {
			i--
		}

		t = nums[i]
		nums[i] = nums[begin]
		nums[begin] = t

		quick_sort(nums, begin, i)
		quick_sort(nums, j, end)
	}
}

func quick_sort_by_index(nums []int, begin, end int, index map[int]int) {
	var i, j, t int

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if index[nums[i]] > index[nums[begin]] {
				// swap
				t = nums[i]
				nums[i] = nums[j]
				nums[j] = t
				j--
			} else {
				i++
			}
		}

		if index[nums[i]] >= index[nums[begin]] {
			i--
		}

		t = nums[i]
		nums[i] = nums[begin]
		nums[begin] = t

		quick_sort_by_index(nums, begin, i, index)
		quick_sort_by_index(nums, j, end, index)
	}
}

func main() {
	var arr1 []int = []int{2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19}
	var arr2 []int = []int{2, 1, 4, 3, 9, 6}

	fmt.Println(relativeSortArray(arr1, arr2))

}
