package main

import "fmt"

const MaxInt = 10000000000

func assertDay(bloomDay []int, day, m, k int) bool {

	f, e := 0, k
	for e <= len(bloomDay) {
		if m == 0 {
			break
		}
		c := 0
		for i := f; i < e; i++ {
			if bloomDay[i]-day > 0 {
				c = 1
				break
			}
		}
		if c == 0 {
			f += k
			e += k
			m -= 1
		} else {
			f += 1
			e += 1
		}
	}

	return m <= 0
}

func minDays(bloomDay []int, m int, k int) int {

	var l int = len(bloomDay)

	if m*k > l {
		return -1
	}
	if m*k == 0 {
		return 0
	}

	l, r := 0, MaxInt
	for l < r {
		mid := l + (r-l)/2
		if assertDay(bloomDay, mid, m, k) {
			r = mid
		} else {
			l = mid + 1
		}
	}
	if l == MaxInt {
		return -1
	}

	return l
}

func main() {

	var bloomDays []int = []int{1000000000, 1000000000}
	var ans int = minDays(bloomDays, 1, 1)
	fmt.Println(ans)
	return
}
