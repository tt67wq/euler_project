package main

import (
	"fmt"
)

const M = 1000000007

func numRollsToTarget(d int, f int, target int) int {
	var cache map[string]int = make(map[string]int)
	return roll(d, f, target, cache)
}

func finger_print(d, target int) string {
	return fmt.Sprintf("%d:%d", d, target)
}

func roll(d, f, target int, cache map[string]int) int {
	if target <= 0 || d <= 0 {
		return 0
	}
	if d == 1 {
		if f >= target {
			return 1
		} else {
			return 0
		}

	}

	var fp string
	var i, ans int

	fp = finger_print(d, target)

	if v, ok := cache[fp]; ok {
		return v
	}

	ans = 0

	for i = 1; i <= f; i++ {
		ans += roll(d-1, f, target-i, cache)
		if ans >= M {
			ans %= M
		}
	}
	cache[fp] = ans
	return ans
}

func main() {
	fmt.Println(numRollsToTarget(30, 30, 500))
}
