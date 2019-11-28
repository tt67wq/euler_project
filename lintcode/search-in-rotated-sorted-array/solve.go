package main

import (
	"fmt"
)

func bin_search(A []int, target, left, right int) int {
	var mid int
	for left+1 < right {
		mid = (left + right) / 2
		if A[mid] > target {
			right = mid
		} else if A[mid] < target {
			left = mid
		} else {
			return mid
		}
	}
	return -1
}

/**
 * @param A: an integer rotated sorted array
 * @param target: an integer to be searched
 * @return: an integer
 */
func search(A []int, target int) int {
	// write your code here
	var left, right int = 0, len(A) - 1
	var mid int
	var ans int

	for left < right && A[left] > A[right] {
		mid = (left + right) / 2
		if A[left] <= A[mid] {
			left = mid + 1
		} else {
			right = mid
		}
	}

	if A[left] == target {
		return left
	}
	// fmt.Printf("min = %d\n", left)
	ans = bin_search(A, target, 0, left-1)
	if ans == -1 {
		ans = bin_search(A, target, left, len(A))
	}
	return ans
}

func main() {
	var A []int = make([]int, 8)
	A = []int{4, 5, 6, 7, 0, 1, 2, 3}

	fmt.Println(search(A, 3))
}
