package main

import (
	"fmt"
)

func abs(num int) int {
	if num > 0 {
		return num
	}
	return 0 - num
}

func switchNums(nums []int, i, j int) {
	t := nums[i]
	nums[i] = nums[j]
	nums[j] = t
}

func quickSort(nums []int, begin, end int) {
	var i, j int

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if abs(nums[i]) > abs(nums[begin]) {
				// swap
				switchNums(nums, i, j)
				j--
			} else {
				i++
			}
		}

		if abs(nums[i]) >= abs(nums[begin]) {
			i--
		}

		switchNums(nums, i, begin)

		quickSort(nums, begin, i)
		quickSort(nums, j, end)
	}

}

func sortedSquares(nums []int) []int {

	var l int = len(nums)
	quickSort(nums, 0, l-1)

	for i := 0; i < l; i++ {
		nums[i] = nums[i] * nums[i]
	}
	return nums
}

func main() {
	var nums []int = []int{-9, -7, -5, -3, -1, 2, 4, 4, 7, 10}
	var res []int = sortedSquares(nums)
	fmt.Println(res)
}
