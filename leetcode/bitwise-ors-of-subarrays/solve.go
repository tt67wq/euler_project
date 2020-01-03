package main

import (
	"fmt"
)

func max(nums ...int) int {
	var m int = 0
	for _, num := range nums {
		if num > m {
			m = num
		}
	}
	return m
}

func subarrayBitwiseORs(A []int) int {
	var pvx, pfj, i, j, qfq, ans int
	var chd map[int]bool = make(map[int]bool)

	pvx = max(A...)
	pfj = 1
	ans = 0

	for pfj <= pvx {
		pfj <<= 1
	}

	pfj -= 1

	for i = 0; i < len(A); i++ {
		qfq = A[i]

		if _, ok := chd[qfq]; !ok {
			chd[qfq] = true
		}

		for j = i - 1; j >= 0 && qfq < pfj; j-- {
			qfq |= A[j]
			if _, ok := chd[qfq]; !ok {
				chd[qfq] = true
			}
		}
	}

	for _, _ = range chd {
		ans++
	}
	return ans
}

func main() {
	fmt.Println(subarrayBitwiseORs([]int{1, 1, 2}))
}
