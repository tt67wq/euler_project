package main

import (
	"fmt"
)

func findClosedNumbers(num int) []int {
	find := 0
	ans := []int{-1, -1}
	sn := 0
	on := uint(0)

	for num > 0 {
		pn := num & (-num)
		num &= num - 1

		if pn&(1<<30) == 0 && num&(pn<<1) == 0 && ans[0] == -1 {
			ans[0] = num | (pn << 1) | (1<<on - 1)
			find++
		}

		if pn > 1 && sn&(pn>>1) == 0 && ans[1] == -1 {
			ans[1] = num | (pn >> 1) | ((pn>>1 - 1) ^ (pn>>1-1)>>on)
		}
		if find == 2 {
			break
		}
		sn |= pn
		on++
	}
	return ans
}

func main() {
	var n int
	for {
		fmt.Scanf("%d", &n)
		fmt.Println(n & (-n))
	}
	return
}
