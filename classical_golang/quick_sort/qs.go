package main

import "fmt"

func sortArray(nums []int) []int {
	quickSort(nums, 0, len(nums)-1)
	return nums
}

func quickSort(nums []int, begin, end int) {
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

		quickSort(nums, begin, i)
		quickSort(nums, j, end)
	}
}

func main() {
	var nums []int = []int{5, 2, 3, 1}

	fmt.Println(sortArray(nums))
}
