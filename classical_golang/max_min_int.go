package main

import (
	"fmt"
)

const MaxUint = ^uint(0)
const MinUint = 0
const MaxInt = int(MaxUint >> 1)
const MinInt = -MaxInt - 1

func min(nums ...int) int {
	var m int = MaxInt
	for _, num := range nums {
		if m > num {
			m = num
		}
	}
	return m
}

func max(nums ...int) int {
	var m int = MinInt
	for _, num := range nums {
		if m < num {
			m = num
		}
	}
	return m
}

func main() {
	fmt.Println(MaxUint, MaxInt, MinUint, MinInt)
}
