package main

import (
	"fmt"
	"math/rand"
)

type Solution struct {
	nums []int
}

func Constructor(nums []int) Solution {
	var s *Solution

	s = new(Solution)
	s.nums = nums

	return *s
}

func (this *Solution) Pick(target int) int {
	var i, num, c, ans int

	c = 0
	for i, num = range this.nums {
		if num == target {
			if rand.Intn(c+1) == 0 {
				ans = i
			}
			c++
		}
	}
	return ans
}

func main() {}
