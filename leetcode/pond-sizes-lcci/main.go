package main

import (
	"fmt"
	"sort"
)

type Pos struct {
	x int
	y int
}

var MAX int = 1000

func pondSizes(land [][]int) []int {

	if len(land) == 0 {
		return nil
	}

	var ans []int

	extend_land := make([][]int, len(land)+2)
	for i := 0; i < len(land)+2; i++ {
		extend_land[i] = make([]int, len(land[0])+2)
	}

	for i := 0; i < len(extend_land); i++ {
		for j := 0; j < len(extend_land[i]); j++ {
			if i == 0 || i == len(extend_land)-1 || j == 0 || j == len(extend_land[i])-1 {
				extend_land[i][j] = 1
			} else {
				extend_land[i][j] = land[i-1][j-1]
			}
		}
	}

	var visit [][]bool = make([][]bool, len(extend_land))
	for i := 0; i < len(extend_land); i++ {
		visit[i] = make([]bool, len(extend_land[i]))
	}

	for i := 1; i < len(extend_land)-1; i++ {
		for j := 1; j < len(extend_land[i])-1; j++ {
			if extend_land[i][j] == 0 && visit[i][j] == false {
				// bfs
				queue := make([]Pos, MAX)
				front := 0
				rear := 0
				area := 1

				queue[front] = Pos{i, j}
				front++
				visit[i][j] = true
				for front != rear {
					tmp := queue[rear]
					rear++

					for x := tmp.x - 1; x <= tmp.x+1; x++ {
						for y := tmp.y - 1; y <= tmp.y+1; y++ {
							if x == tmp.x && y == tmp.y {
								continue
							}
							if extend_land[x][y] == 0 && visit[x][y] == false {
								area += 1
								queue[front] = Pos{x, y}
								front += 1
								visit[x][y] = true
							}
						}
					}
				}
				ans = append(ans, area)
			}
		}
	}

	// sort
	sort.Slice(ans, func(i, j int) bool {
		return ans[i] < ans[j]
	})
	return ans
}

func main() {
	land := [][]int{{0, 2, 1, 0}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}}
	fmt.Println(pondSizes(land))
	return
}
