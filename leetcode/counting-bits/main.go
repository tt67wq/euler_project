package main

import "fmt"

func countBits(num int) []int {
	var res []int = make([]int, num+1)

	res[0] = 0
	var stop bool = true
	for n := 0; stop; n++ {
		j := 1 << n
		for i := 0; i < j; i++ {
			if i+j > num {
				stop = false
				break
			}
			res[i+j] = res[i] + 1
		}
	}
	return res
}

func main() {
	res := countBits(5)
	fmt.Println(res)
}
