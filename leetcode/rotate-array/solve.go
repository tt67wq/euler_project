package main

import (
	"fmt"
)

func rotate_once(nums []int, l int) {
	var i, j, t int

	t = nums[l-1]
	for i = 0; i < l; i++ {
		j = nums[i]
		nums[i] = t
		t = j
	}
}

func rotate(nums []int, k int) {
	var i, l int
	l = len(nums)
	k %= l
	for i = 0; i < k; i++ {
		rotate_once(nums, l)
	}
}

func main() {

	var nums []int = []int{1, 2, 3, 4, 5, 6, 7}
	rotate(nums, 3)
	fmt.Println(nums)
}
