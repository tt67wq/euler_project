package main

import (
	"fmt"
)

/**
 * @param numbers: An array of Integer
 * @param target: target = numbers[index1] + numbers[index2]
 * @return: [index1, index2] (index1 < index2)
 */
func twoSum(numbers []int, target int) []int {

	var ans []int = make([]int, 2)
	var i, j, l int
	l = len(numbers)
	for i = 0; i < l-1; i++ {
		for j = i + 1; j < l; j++ {
			if numbers[i]+numbers[j] == target {
				ans[0] = i
				ans[1] = j
				break
			}
		}
	}

	return ans
}

func main() {
	numbers := []int{0, 4, 3, 0}
	fmt.Println(twoSum(numbers, 0))
	return
}
