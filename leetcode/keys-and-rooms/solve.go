package main

import (
	"fmt"
)

func canVisitAllRooms(rooms [][]int) bool {
	var vis []bool
	var i int

	vis = make([]bool, len(rooms))

	dfs(rooms, 0, vis)

	for i = 1; i < len(vis); i++ {
		if !vis[i] {
			return false
		}
	}
	return true
}

func dfs(rooms [][]int, idx int, vis []bool) {
	var keys []int
	var i int

	keys = rooms[idx]

	for i = 0; i < len(keys); i++ {
		if !vis[keys[i]] {
			vis[keys[i]] = true
			dfs(rooms, keys[i], vis)
		}
	}
}

func main() {
	fmt.Println(canVisitAllRooms([][]int{{1}, {2}, {3}, {}}))
}
