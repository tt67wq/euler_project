package main

import (
	"fmt"
)

func findPoisonedDuration(timeSeries []int, duration int) int {
	// Write your code here
	if len(timeSeries) == 0 {
		return 0
	}
	if len(timeSeries) == 1 {
		return duration
	}

	var vis map[int]int = make(map[int]int)
	var ts, i, ans int

	for _, ts = range timeSeries {
		for i = 0; i < duration; i++ {
			vis[ts+i] = 1
		}
	}
	ans = 0
	for _, _ = range vis {
		ans++
	}
	return ans
}

func main() {
	timeSeries := []int{1}
	fmt.Println(findPoisonedDuration(timeSeries, 2))
}
