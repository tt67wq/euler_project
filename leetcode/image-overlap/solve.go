package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func largestOverlap(A [][]int, B [][]int) int {
	var i, j, k, l, t, m int
	var deltas [][]int // 位移

	l = len(A)
	deltas = make([][]int, 0)

	k = 0
	for i = 1 - l; i < l; i++ {
		for j = 1 - l; j < l; j++ {
			deltas = append(deltas, []int{i, j})
			k++
		}
	}

	m = MinInt
	for i = 0; i < k; i++ {
		t = overlap(A, B, deltas[i])
		if t > m {
			m = t
		}
	}

	return m
}

func abs(n int) int {
	if n < 0 {
		return -n
	}
	return n
}

func overlap(A, B [][]int, delta []int) int {
	var i, j, ans int

	for i = 0; i < len(A); i++ {
		for j = 0; j < len(A); j++ {
			if i+delta[0] >= 0 && i+delta[0] < len(A) && j-delta[1] >= 0 && j-delta[1] < len(A) {
				if B[i][j] == 1 && A[i+delta[0]][j-delta[1]] == 1 {
					ans++
				}
			}
		}
	}

	return ans
}

func main() {
	largestOverlap([][]int{{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}, [][]int{{0, 0, 0}, {0, 1, 1}, {0, 0, 1}})
}
