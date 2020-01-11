package main

import (
	"fmt"
)

func combinationSum(candidates []int, target int) [][]int {
	var ans [][]int = make([][]int, 0)
	dfs(candidates, []int{}, 0, target, &ans)
	return ans
}

func dfs(candidates, res []int, acc, target int, ans *[][]int) {
	if acc == target {
		var tmp []int
		tmp = make([]int, len(res))
		copy(tmp, res)
		*ans = append(*ans, tmp)
		return
	}

	var elem int

	for _, elem = range candidates {
		if elem+acc <= target {
			if len(res) > 0 {
				if elem >= res[len(res)-1] {
					res = append(res, elem)
					dfs(candidates, res, acc+elem, target, ans)
					res = res[:len(res)-1]
				}
			} else {
				res = append(res, elem)
				dfs(candidates, res, acc+elem, target, ans)
				res = []int{}
			}

		}
	}
}

func main() {
	var candidates []int = []int{2, 3, 5}
	dfs(candidates, []int{}, 0, 8)
}
