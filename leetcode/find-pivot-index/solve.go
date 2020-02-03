package main

import (
	"fmt"
)

func sum(nums ...int) int {
	var s, i int
	s = 0

	for _, i = range nums {
		s += i
	}
	return s
}

func pivotIndex(nums []int) int {
	if len(nums) < 3 {
		return -1
	}
	var i, left, right int

	left = 0
	right = sum(nums[1:]...)

	i = 0
	for left != right && i < len(nums)-1 {
		// fmt.Println(left, right)
		left += nums[i]
		right -= nums[i+1]
		i++
	}
	if left == right {
		return i
	}
	return -1
}

func main() {
	fmt.Println(pivotIndex([]int{-1, -1, -1, 0, 1, 1}))
}
