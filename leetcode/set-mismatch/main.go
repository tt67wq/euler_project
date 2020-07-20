package main

import "fmt"

func sortArray(nums []int) {
	quick_sort(nums, 0, len(nums)-1)
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

func findErrorNums(nums []int) []int {
	sortArray(nums)
	var repeat int = 0
	var absent int = 1

	fmt.Println(nums)
	for i, num := range nums {
		if i > 0 {
			if nums[i] == nums[i-1] {
				repeat = num
			} else if nums[i]-nums[i-1] > 1 {
				absent = nums[i-1] + 1
			}
		}

	}
	if len(nums) != nums[len(nums)-1] {
		absent = len(nums)
	}

	return []int{repeat, absent}
}

func main() {
	fmt.Println(findErrorNums([]int{2, 2}))
	fmt.Println(findErrorNums([]int{1, 2, 2, 4}))
	fmt.Println(findErrorNums([]int{3, 2, 3, 4, 6, 5}))
	fmt.Println(findErrorNums([]int{1, 5, 3, 2, 2, 7, 6, 4, 8, 9}))

	return
}
