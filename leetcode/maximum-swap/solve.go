package main

import (
	"fmt"
	"strconv"
)

func swap(num, i, j int) int {
	var ns string
	var bs []byte
	var t byte
	var res int

	ns = strconv.Itoa(num)
	bs = []byte(ns)

	t = bs[i]
	bs[i] = bs[j]
	bs[j] = t

	res, _ = strconv.Atoi(string(bs))
	return res
}

func num_len(num int) int {
	var l int
	l = 0

	for num > 0 {
		l++
		num /= 10
	}
	return l
}

func maximumSwap(num int) int {

	var i, j, l, ans, t int

	l = num_len(num)

	if l == 1 {
		return num
	}

	ans = num
	for i = 0; i < l-1; i++ {
		for j = i + 1; j < l; j++ {
			t = swap(num, i, j)
			if t > ans {
				ans = t
			}
		}
	}
	return ans
}

func main() {
	var num int
	for {
		fmt.Scanf("%d", &num)
		fmt.Println(maximumSwap(num))
	}

}
