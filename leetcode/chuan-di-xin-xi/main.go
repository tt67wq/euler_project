package main

import "fmt"

func dfs(relation [][]int, cur, ki, k, n int, c *int) {
	if ki == k {
		if cur == n-1 {
			(*c)++
		}
		return
	}

	for _, pair := range relation {
		if pair[0] == cur {
			dfs(relation, pair[1], ki+1, k, n, c)
		}
	}
}

func numWays(n int, relation [][]int, k int) int {

	var res int = 0
	dfs(relation, 0, 0, k, n, &res)
	return res
}

func main() {
	relation := [][]int{{0, 2}, {2, 1}, {3, 4}, {2, 3}, {1, 4}, {2, 0}, {0, 4}}

	fmt.Println(numWays(5, relation, 3))
}
