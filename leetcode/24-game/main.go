package main

import (
	"fmt"
)

type RealNum struct {
	m int
	n int
}

func choose_and_calculate(nums []RealNum) [][]RealNum {
	var res [][]RealNum
	actions := []string{"+", "-", "*", "/", "~", "#"}

	if len(nums) == 2 {
		for _, action := range actions {
			if ok, tmp := calculate(nums[0], nums[1], action); ok {
				res = append(res, []RealNum{tmp})
			}
		}
	} else if len(nums) == 3 {
		for _, action := range actions {
			if ok, tmp := calculate(nums[0], nums[1], action); ok {
				res = append(res, []RealNum{tmp, nums[2]})
			}
			if ok, tmp := calculate(nums[0], nums[2], action); ok {
				res = append(res, []RealNum{tmp, nums[1]})
			}
			if ok, tmp := calculate(nums[1], nums[2], action); ok {
				res = append(res, []RealNum{tmp, nums[0]})
			}
		}
	} else if len(nums) == 4 {

		for _, action := range actions {
			if ok, tmp := calculate(nums[0], nums[1], action); ok {
				res = append(res, []RealNum{tmp, nums[2], nums[3]})
			}
			if ok, tmp := calculate(nums[0], nums[2], action); ok {
				res = append(res, []RealNum{tmp, nums[1], nums[3]})
			}
			if ok, tmp := calculate(nums[0], nums[3], action); ok {
				res = append(res, []RealNum{tmp, nums[1], nums[2]})
			}
			if ok, tmp := calculate(nums[1], nums[2], action); ok {
				res = append(res, []RealNum{tmp, nums[0], nums[3]})
			}
			if ok, tmp := calculate(nums[1], nums[3], action); ok {
				res = append(res, []RealNum{tmp, nums[0], nums[2]})
			}
			if ok, tmp := calculate(nums[2], nums[3], action); ok {
				res = append(res, []RealNum{tmp, nums[1], nums[0]})
			}
		}
	}

	return res
}

func gcd(m, n int) int {
	if m == 0 || n == 0 {
		return 1
	}

	var r int
	var direction int = 1
	if m < 0 {
		m = -m
		direction *= -1
	}
	if n < 0 {
		n = -n
		direction *= -1
	}

	r = m % n
	if r > 0 {
		return direction * gcd(n, r)
	}
	return n
}

func isEqual(a, b RealNum) bool {
	return a.m*b.n-b.m*a.n == 0
}

func calculate(a, b RealNum, action string) (bool, RealNum) {
	if action == "+" {
		m := a.m*b.n + b.m*a.n
		n := a.n * b.n
		g := gcd(m, n)
		return true, RealNum{m / g, n / g}
	}
	if action == "*" {
		m := a.m * b.m
		n := a.n * b.n
		g := gcd(m, n)
		return true, RealNum{m / g, n / g}
	}
	if action == "-" {
		m := a.m*b.n - b.m*a.n
		n := a.n * b.n
		g := gcd(m, n)
		return true, RealNum{m / g, n / g}
	}
	if action == "/" {
		if b.m != 0 {
			m := a.m * b.n
			n := a.n * b.m
			g := gcd(m, n)
			return true, RealNum{m / g, n / g}
		} else {
			return false, RealNum{0, 0}
		}
	}
	if action == "~" {
		m := b.m*a.n - a.m*b.n
		n := a.n * b.n
		g := gcd(m, n)
		return true, RealNum{m / g, n / g}
	}

	if action == "#" {
		if a.m != 0 {
			m := b.m * a.n
			n := b.n * a.m
			g := gcd(m, n)
			return true, RealNum{m / g, n / g}
		} else {
			return false, RealNum{0, 0}
		}
	}
	return false, RealNum{0, 0}
}

func judgePoint24(nums []int) bool {

	nums1 := []RealNum{RealNum{nums[0], 1}, RealNum{nums[1], 1}, RealNum{nums[2], 1}, RealNum{nums[3], 1}}

	for _, nums2 := range choose_and_calculate(nums1) {
		for _, nums3 := range choose_and_calculate(nums2) {
			for _, nums4 := range choose_and_calculate(nums3) {
				if len(nums4) > 0 && isEqual(nums4[0], RealNum{24, 1}) {
					return true
				}
			}
		}
	}

	return false
}

func main() {
	fmt.Println(judgePoint24([]int{1, 2, 1, 2}))
	return
}
