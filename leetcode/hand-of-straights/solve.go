package main

import (
	"fmt"
)

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

func isNStraightHand(hand []int, W int) bool {
	if len(hand)%W != 0 {
		return false
	}

	var i, j int
	var vis map[int]int = make(map[int]int)

	for i = 0; i < len(hand); i++ {
		vis[hand[i]]++
	}

	quick_sort(hand, 0, len(hand)-1)

	for i = 0; i < len(hand); i++ {
		if vis[hand[i]] > 0 {
			for j = 0; j < W; j++ {
				vis[hand[i]+j]--
				if vis[hand[i]+j] < 0 {
					return false
				}
			}
		}
	}
	return true
}

func main() {
	fmt.Println(isNStraightHand([]int{1, 2, 3, 6, 2, 3, 4, 7, 8}, 3))
}
