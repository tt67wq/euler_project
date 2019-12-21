package main

import (
	"fmt"
)

func isIdealPermutation(A []int) bool {
	if len(A) < 3 {
		return true
	}

	var mx []int = make([]int, len(A))
	var i int

	mx[0] = A[0]

	// max
	for i = 1; i < len(A); i++ {
		if A[i] > mx[i-1] {
			mx[i] = A[i]
		} else {
			mx[i] = mx[i-1]
		}
	}

	// fmt.Println(mx, A)
	// 全局一定包含局部
	for i = 2; i < len(A); i++ {
		if A[i] < A[i-1] {
			// 局部
			if A[i] < mx[i-2] {
				return false
			}
		} else {
			// 升序
			if A[i] != mx[i] {
				return false
			}
		}
	}
	return true
}

func main() {
	fmt.Println(isIdealPermutation([]int{1, 0, 2}))
	fmt.Println(isIdealPermutation([]int{1, 2, 0}))
	fmt.Println(isIdealPermutation([]int{0, 2, 1}))

}
