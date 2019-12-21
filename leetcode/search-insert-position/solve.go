package main

import (
	"fmt"
)

func searchInsert(nums []int, target int) int {
	var i, j, m int

	i = 0
	j = len(nums) - 1

	for i+1 < j {
		m = (i + j) / 2
		if target > nums[m] {
			i = m
		} else if target < nums[m] {
			j = m
		} else {
			return m
		}
	}
	// i == j or i+1 == j

	if i == j {
		if target > nums[i] {
			return i + 1
		} else {
			return i
		}
	}

	if i+1 == j {
		if target <= nums[i] {
			return i
		} else if target <= nums[j] {
			return j
		} else {
			return j + 1
		}
	}
	return 0
}

func main() {
	fmt.Println(searchInsert([]int{1, 3, 5, 6}, 7))
	fmt.Println(searchInsert([]int{1, 3, 5, 6}, 4))
	fmt.Println(searchInsert([]int{1, 3, 5, 6}, 5))
	fmt.Println(searchInsert([]int{1, 3, 5, 6}, 1))
	fmt.Println(searchInsert([]int{1, 3, 5, 7}, 6))
}
