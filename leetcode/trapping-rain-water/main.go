package main

import "fmt"

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func trap(height []int) int {
	if len(height) == 0 {
		return 0
	}

	var ans int = 0
	var size int = len(height)

	var leftMax []int = make([]int, size)
	var rightMax []int = make([]int, size)

	leftMax[0] = height[0]

	for i := 1; i < size; i++ {
		leftMax[i] = max(height[i], leftMax[i-1])
	}

	rightMax[size-1] = height[size-1]
	for i := size - 2; i >= 0; i-- {
		rightMax[i] = max(height[i], rightMax[i+1])
	}

	for i := 1; i < size-1; i++ {
		ans += (min(leftMax[i], rightMax[i]) - height[i])
	}
	return ans
}

func main() {
	fmt.Println(trap([]int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}))
}
