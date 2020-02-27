package main

import (
	"fmt"
)

const M int = 1000000007

func quick_sort(nums []int, begin, end int) {
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

		quick_sort(nums, begin, i)
		quick_sort(nums, j, end)
	}
}

func threeSumMulti(A []int, target int) int {
	var i, l, t, j, k, tmp, d, left, right, ans int

	l = len(A)
	quick_sort(A, 0, l-1)

	for i = 0; i < l; i++ {
		t = target - A[i]
		if t < 0 {
			break
		}

		j, k = i+1, l-1
		for j < k {
			tmp = A[j] + A[k]
			if tmp < t {
				j++
			} else if tmp > t {
				k--
			} else {
				// 命中
				if A[j] == A[k] {
					d = k - j + 1
					ans += d * (d - 1) / 2
					ans %= M
					break
				} else {
					left, right = 1, 1
					for j+1 < k && A[j] == A[j+1] {
						left++
						j++
					}
					for k-1 > j && A[k] == A[k-1] {
						right++
						k--
					}
					ans += left * right
					ans %= M

					j++
					k--
				}
			}
		}
	}
	return ans
}

func main() {
	fmt.Println(threeSumMulti([]int{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 8))
	fmt.Println(threeSumMulti([]int{1, 1, 2, 2, 2, 2}, 5))
}
