package main

import (
	"fmt"
)

func removeDuplicates(nums []int) int {
	if len(nums) <= 1 {
		return len(nums)
	}

	var i, j int
	i = 0
	j = 1

	for j < len(nums) {
		if nums[i] == nums[j] {
			j++
		} else {
			//
			i++
			nums[i] = nums[j]
			j++
		}
	}
	return i + 1
}

func main() {
	fmt.Println(removeDuplicates([]int{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}))
}
