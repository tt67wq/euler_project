package main

import "fmt"

func reversePairs(nums []int) int {
	return mergeSort(nums, 0, len(nums)-1)
}

func mergeSort(nums []int, start, end int) int {
	// fmt.Println(start, end)
	if start >= end {
		return 0
	}

	mid := start + (end-start)/2
	cnt := mergeSort(nums, start, mid) + mergeSort(nums, mid+1, end)
	tmp := []int{}

	i, j := start, mid+1
	for i <= mid && j <= end {
		if nums[i] <= nums[j] {
			tmp = append(tmp, nums[i])
			cnt += j - (mid + 1)
			i++
		} else {
			tmp = append(tmp, nums[j])
			j++
		}
	}

	for ; i <= mid; i++ {
		tmp = append(tmp, nums[i])
		cnt += end - (mid + 1) + 1
	}

	for ; j <= end; j++ {
		tmp = append(tmp, nums[j])
	}

	for i := start; i <= end; i++ {
		nums[i] = tmp[i-start]
	}

	return cnt
}

func main() {
	fmt.Println(reversePairs([]int{7, 5, 6, 4}))
}
