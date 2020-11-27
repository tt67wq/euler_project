package main

import "fmt"

func constructArray(n int, k int) []int {
	var ans []int

	for i := 1; i < n-k; i++ {
		ans = append(ans, i)
	}

	i := 1
	j := k + 1
	for i < j {
		ans = append(ans, i+n-k-1)
		ans = append(ans, j+n-k-1)
		i++
		j--
	}
	if i == j {
		ans = append(ans, i+n-k-1)
	}

	return ans
}

func main() {
	var ans []int = constructArray(3, 2)
	fmt.Println(ans)
}
