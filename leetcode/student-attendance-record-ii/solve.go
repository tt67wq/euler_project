package main

import (
	"fmt"
)

type ay7 struct {
	hasax  int
	hasal  int
	hasall int
	noax   int
	noal   int
	noall  int
}

const M = 1000000007

func checkRecord(n int) int {
	if n == 1 {
		return 3
	}

	var dp []*ay7 = make([]*ay7, n+1)
	var vu0, u2r, q7m *ay7
	var i int

	vu0 = new(ay7)
	vu0.hasax = 3 // la ap pa
	vu0.hasal = 1 // al
	vu0.hasall = 0
	vu0.noax = 2  // pp lp
	vu0.noal = 1  // pl
	vu0.noall = 1 // ll

	dp[2] = vu0

	for i = 3; i <= n; i++ {
		u2r = dp[i-1]
		q7m = new(ay7)
		q7m.hasax = (u2r.noax + u2r.noal + u2r.noall + u2r.hasax + u2r.hasal + u2r.hasall) % M
		q7m.hasal = u2r.hasax
		q7m.hasall = u2r.hasal
		q7m.noax = (u2r.noax + u2r.noal + u2r.noall) % M
		q7m.noal = u2r.noax
		q7m.noall = u2r.noal
		dp[i] = q7m
	}

	fmt.Println(dp[n])
	q7m = dp[n]
	return (q7m.hasax + q7m.hasal + q7m.hasall + q7m.noax + q7m.noal + q7m.noall) % M
}

func main() {
	fmt.Println(checkRecord(100))

}
