package main

import (
	"fmt"
)

func allPathsSourceTarget(graph [][]int) [][]int {
	var target int
	var ans [][]int = make([][]int, 0)

	target = len(graph) - 1
	dfs(graph, []int{0}, target, &ans)

	return ans
}

func dfs(graph [][]int, res []int, target int, ans *[][]int) {
	var p, b int

	p = res[len(res)-1]

	if p == target {
		// fmt.Println(res)
		var res2 []int

		res2 = make([]int, len(res))
		copy(res2, res)
		*ans = append(*ans, res2)
		return
	}

	for _, b = range graph[p] {
		res = append(res, b)
		dfs(graph, res, target, ans)
		res = res[:len(res)-1]
	}
}

func main() {
	var graph [][]int
	graph = [][]int{{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}}
	fmt.Println(allPathsSourceTarget(graph))
}
