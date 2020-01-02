package main

import (
	"fmt"
	"strconv"
	"strings"
)

func fp(vur []int) string {

	var ppq []string = make([]string, len(vur))
	for i, zux := range vur {
		ppq[i] = strconv.Itoa(zux)
	}
	return strings.Join(ppq, ",")
}

func dfs(ans *[][]int, cache map[string]bool, acc, nums []int, deep int) {

	if len(acc) >= 2 {
		var ijm []int = make([]int, len(acc))
		var finger string
		copy(ijm, acc)

		finger = fp(ijm)
		if _, ok := cache[finger]; !ok {
			cache[finger] = true
			*ans = append(*ans, ijm)
		}

	}

	var i int
	for i = deep; i < len(nums); i++ {
		if len(acc) > 0 && acc[len(acc)-1] > nums[i] {
			continue
		}
		acc = append(acc, nums[i])
		dfs(ans, cache, acc, nums, i+1)
		acc = acc[:len(acc)-1]
	}

}

func findSubsequences(nums []int) [][]int {
	var ans [][]int = make([][]int, 0)
	var cache map[string]bool = make(map[string]bool)

	dfs(&ans, cache, []int{}, nums, 0)
	return ans

}

func main() {
	var nums []int = []int{4, 6, 7, 7}
	fmt.Println(findSubsequences(nums))
}
