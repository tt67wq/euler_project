package main

import (
	"fmt"
	"strconv"
	"strings"
)

func quickSort(nums []int, begin, end int) {
	var i, j, t int

	if begin < end {
		i = begin + 1
		j = end
		for i < j {
			if nums[i] > nums[begin] {
				// swap
				t = nums[i]
				nums[i] = nums[j]
				nums[j] = t
				j--
			} else {
				i++
			}
		}

		if nums[i] >= nums[begin] {
			i--
		}

		t = nums[i]
		nums[i] = nums[begin]
		nums[begin] = t

		quickSort(nums, begin, i)
		quickSort(nums, j, end)
	}
}

func reverse(s []int) []int {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}

func largestMultipleOfThree(digits []int) string {
	var m0, m1, m2, drop []int
	var s int = 0

	quickSort(digits, 0, len(digits)-1)
	for _, d := range digits {
		if d%3 == 0 {
			m0 = append(m0, d)
		} else if d%3 == 1 {
			m1 = append(m1, d)
		} else {
			m2 = append(m2, d)
		}
		s += d
	}

	// quickSort(m1, 0, len(m1)-1)
	// quickSort(m2, 0, len(m2)-1)

	if s%3 == 0 {
		// pass
	} else if s%3 == 1 {
		if len(m1) > 0 {
			// drop smallest from m1
			drop = append(drop, m1[0])

		} else {
			// drop 2 smallest from m2
			drop = append(drop, m2[0])
			drop = append(drop, m2[1])
		}
	} else {
		if len(m2) > 0 {
			drop = append(drop, m2[0])
		} else {
			drop = append(drop, m1[0])
			drop = append(drop, m1[1])
		}
	}

	var res []string

	reverse(digits)

	for _, n := range digits {
		flag := false
		for i, dr := range drop {
			if n == dr {
				drop = append(drop[:i], drop[i+1:]...)
				flag = true
				break
			}
		}
		if !flag {
			res = append(res, strconv.Itoa(n))
		}

	}

	if len(res) > 0 && res[0] == "0" {
		return "0"
	}
	return strings.Join(res, "")
}

func main() {
	for _, nums := range [][]int{{8, 6, 7, 1, 0}, {8, 1, 9}, {1}, {0, 0, 0, 0}, {1, 1, 1, 2}, {2, 2, 1, 1, 1}} {
		res := largestMultipleOfThree(nums)
		fmt.Println(res)
	}
}
