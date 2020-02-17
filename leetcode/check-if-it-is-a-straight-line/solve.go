package main

import (
	"fmt"
)

func get_k(a, b []int) float64 {
	return float64(b[1]-a[1]) / float64(b[0]-a[0])
}

func checkStraightLine(coordinates [][]int) bool {
	var a, b []int
	var i int
	var k float64

	a = coordinates[0]
	b = coordinates[1]

	k = get_k(a, b)

	for i = 2; i < len(coordinates); i++ {
		if get_k(coordinates[i], a) != k {
			return false
		}
	}
	return true
}

func main() {
	fmt.Println(checkStraightLine([][]int{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}}))
}
