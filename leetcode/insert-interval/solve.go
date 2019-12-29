package main

import (
	"fmt"
)

// 二分查看落在那个区间中
func bin_search(intervals [][]int, num int) (int, bool) {
	var i, j, m int

	i = 0
	j = len(intervals) - 1

	for i+1 < j {
		m = (i + j) / 2
		if num < intervals[m][0] {
			// left
			j = m
		} else if num > intervals[m][1] {
			// right
			i = m
		} else {
			// in this block
			return m, true
		}
	}

	// i+1 == j || i == j
	if i == j {
		// 1 block
		if num < intervals[i][0] {
			return i - 1, false
		} else if num > intervals[i][1] {
			return i + 1, false
		} else {
			return i, true
		}
	} else {
		// 2 blocks
		// ..[i0, i1]..[j0, j1]..
		if num < intervals[i][0] {
			return i, false
		} else if num <= intervals[i][1] {
			return i, true
		} else if num < intervals[j][0] {
			return j, false
		} else if num <= intervals[j][1] {
			return j, true
		} else {
			return j + 1, false
		}
	}
}

func insert(intervals [][]int, newInterval []int) [][]int {
	var a, b int
	var ha, hb bool
	var ans [][]int = make([][]int, 0)

	a, ha = bin_search(intervals, newInterval[0])
	b, hb = bin_search(intervals, newInterval[1])

	fmt.Println(a, ha)
	fmt.Println(b, hb)

	if ha && hb {
		ans = append(intervals[:a], []int{intervals[a][0], intervals[b][1]})
		ans = append(ans, intervals[b+1:]...)
	} else if !ha && hb {
		ans = append(intervals[:a], []int{newInterval[0], intervals[b][1]})
		ans = append(ans, intervals[b+1:]...)
	} else if ha && !hb {
		ans = append(intervals[:a], []int{intervals[a][0], newInterval[1]})
		ans = append(ans, intervals[b:]...)
	} else {
		// !ha && !hb
		if a == b {

		}
		ans = append(intervals[:a], []int{newInterval[0], newInterval[1]})
		ans = append(ans, intervals[b:]...)

	}

	return ans
}

func main() {
	// fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{2, 6}))
	// fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{0, 6}))
	// fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{4, 6}))
	// fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{3, 5}))
	// fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{3, 10}))
	fmt.Println(insert([][]int{{1, 3}, {6, 9}}, []int{4, 5}))

}
