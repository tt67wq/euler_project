package main

import (
	"fmt"
)

type pos struct {
	x int
	y int
	d int
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}

func allCellsDistOrder(R int, C int, r0 int, c0 int) [][]int {

	var r, c, n int
	var ps []pos = make([]pos, 0)
	var tp *pos
	var tpv pos
	var ans [][]int = make([][]int, 0)

	n = 0
	for r = 0; r < R; r++ {
		for c = 0; c < C; c++ {
			tp = new(pos)
			tp.x = r
			tp.y = c
			tp.d = abs(r-r0) + abs(c-c0)

			ps = append(ps, *tp)
			n++
		}
	}

	// sort
	quick_sort(ps, 0, n-1)
	for _, tpv = range ps {
		ans = append(ans, []int{tpv.x, tpv.y})
	}

	return ans
}

func quick_sort(ps []pos, begin, end int) {
	var i, j int
	var t pos

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if ps[i].d > ps[begin].d {
				// swap
				t = ps[i]
				ps[i] = ps[j]
				ps[j] = t
				j--
			} else {
				i++
			}
		}

		if ps[i].d >= ps[begin].d {
			i--
		}

		t = ps[i]
		ps[i] = ps[begin]
		ps[begin] = t

		quick_sort(ps, begin, i)
		quick_sort(ps, j, end)
	}
}

func main() {
	// R = 1, C = 2, r0 = 0, c0 = 0
	fmt.Println(allCellsDistOrder(2, 2, 0, 1))
}
