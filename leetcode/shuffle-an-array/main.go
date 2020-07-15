package main

import (
	"fmt"
	"math/rand"
	"time"
)

type Solution struct {
	nums []int
}

func Constructor(nums []int) Solution {
	s := new(Solution)
	s.nums = nums
	return *s
}

/** Resets the array to its original configuration and return it. */
func (this *Solution) Reset() []int {
	return this.nums
}

func remove(slice []int, s int) []int {
	return append(slice[:s], slice[s+1:]...)
}

/** Returns a random shuffling of the array. */
func (this *Solution) Shuffle() []int {
	var l int = len(this.nums)
	var nums []int = make([]int, l)
	var ans []int

	copy(nums, this.nums)
	for l > 0 {
		i := rand.Intn(l)
		ans = append(ans, nums[i])
		remove(nums, i)
		l--
	}
	return ans
}

func main() {
	s := Constructor([]int{1, 2, 3})
	for {
		fmt.Print("> ")
		fmt.Println(s.Shuffle())
		time.Sleep(time.Duration(2) * time.Second)
	}

}
