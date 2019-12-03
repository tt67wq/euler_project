package main

import (
	"fmt"
)

func distance(p1 []int, p2 []int) int {
	return (p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1])
}

func validSquare(p1 []int, p2 []int, p3 []int, p4 []int) bool {
	var d int
	var mp map[int]int = make(map[int]int)
	for _, d = range []int{distance(p1, p2), distance(p1, p3), distance(p1, p4), distance(p2, p3), distance(p2, p4), distance(p3, p4)} {
		if d == 0 {
			return false
		}
		mp[d]++
	}
	return len(mp) == 2
}

func main() {
	// [0,0]
	// [5,0]
	// [5,4]
	// [0,4]
	fmt.Println(validSquare([]int{0, 0}, []int{5, 0}, []int{5, 5}, []int{0, 5}))
}
