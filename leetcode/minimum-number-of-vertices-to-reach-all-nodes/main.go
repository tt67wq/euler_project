package main

import "fmt"

func findSmallestSetOfVertices(n int, edges [][]int) []int {
	var vis map[int][]int = make(map[int][]int)

	// init [into, out]
	for i := 0; i < n; i++ {
		vis[i] = []int{0, 0}
	}

	for i := 0; i < len(edges); i++ {
		vis[edges[i][0]][1]++
		vis[edges[i][1]][0]++
	}

	var ans []int
	for i := 0; i < n; i++ {
		if vis[i][0] == 0 {
			ans = append(ans, i)
		}
	}
	return ans
}

func main() {
	var edges [][]int = [][]int{{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}}

	ans := findSmallestSetOfVertices(6, edges)
	fmt.Println(ans)
}
