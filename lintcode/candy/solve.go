package main

import (
	"fmt"
	// "sort"
)

func max(ns ...int) int {
	var mx int = ns[0]
	var n int
	for _, n = range ns {
		if n > mx {
			mx = n
		}
	}
	return mx
}

/**
 * @param ratings: Children's ratings
 * @return: the minimum candies you must give
 */
func candy(ratings []int) int {
	// write your code here
	var ans int = 0
	var vis []int = make([]int, len(ratings))
	var i int

	// sort.Ints(ratings)

	for i = 0; i < len(ratings); i++ {
		vis[i] = 1
	}

	if ratings[0] > ratings[1] {
		vis[0] += 1
	}

	for i = 1; i < len(ratings); i++ {
		if ratings[i] > ratings[i-1] {
			vis[i] = vis[i-1] + 1
		}
	}
	// fmt.Println(vis)
	// fmt.Println(ratings)

	for i = len(ratings) - 2; i > -1; i-- {
		if ratings[i] > ratings[i+1] {
			vis[i] = max(vis[i], vis[i+1]+1)
		}
	}

	// fmt.Println(vis)
	// fmt.Println(ratings)

	for i = 0; i < len(ratings); i++ {
		ans += vis[i]
	}

	return ans
}

func main() {

	fmt.Println(candy([]int{1, 3, 4, 3, 2, 1}))
	fmt.Println(candy([]int{4, 2, 3, 4, 1}))
	fmt.Println(candy([]int{2, 1}))
	fmt.Println(candy([]int{1, 2}))
	fmt.Println(candy([]int{1, 2, 2}))
}
