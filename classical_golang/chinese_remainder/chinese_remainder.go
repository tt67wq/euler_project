package main

import (
	"fmt"
)

// 扩展欧几里得算法
func egcd(a, b int) int {
	var a1, a2, b1, b2, c, tmp int
	a1 = 0
	a2 = 1
	b1 = 1
	b2 = 0

	for b != 0 {
		c = a / b
		tmp = a
		a = b
		b = tmp % b

		tmp = a1
		a1 = a2 - c*a1
		a2 = tmp

		tmp = b1
		b1 = b2 - c*b1
		b2 = tmp
	}
	return a2
}

// 求逆元 即 a*x = 1 mod b
func inverse(a, b int) int {
	var g int
	g = egcd(a, b)
	if g > 0 {
		return g
	}
	return b + g
}

// 中国剩余定理, 即解下面方程组
// x = b0 mod a0
// x = b1 mod a1
// x = b2 mod a2
// ...
// x = crt([[a0, b0], [a1, b1], [a2, b2]...])
func crt(pairs [][]int) int {
	var i, l, product, ans int
	var ms, rs, mis, ins []int

	l = len(pairs)

	ms = make([]int, l)
	rs = make([]int, l)
	mis = make([]int, l)
	ins = make([]int, l)

	for i = 0; i < l; i++ {
		ms[i] = pairs[i][0]
		rs[i] = pairs[i][1]
	}
	product = 1

	for i = 0; i < l; i++ {
		product *= ms[i]
	}

	for i = 0; i < l; i++ {
		mis[i] = product / ms[i]
		ins[i] = inverse(mis[i], ms[i])
	}

	ans = 0
	for i = 0; i < l; i++ {
		ans += mis[i] * ins[i] * rs[i]
		ans %= product
	}
	return ans
}

func main() {
	fmt.Println(crt([][]int{{3, 2}, {5, 3}, {7, 2}}))
}
