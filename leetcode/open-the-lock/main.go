package main

import (
	"fmt"
)

var QUEUE_SIZE int = 10000

func replaceAtIndex(in string, r rune, i int) string {
	out := []rune(in)
	out[i] = r
	return string(out)
}

var CHANGE_MAP map[rune][]rune = map[rune][]rune{
	'0': []rune{'1', '9'},
	'1': []rune{'2', '0'},
	'2': []rune{'3', '1'},
	'3': []rune{'4', '2'},
	'4': []rune{'5', '3'},
	'5': []rune{'6', '4'},
	'6': []rune{'7', '5'},
	'7': []rune{'8', '6'},
	'8': []rune{'9', '7'},
	'9': []rune{'0', '8'},
}

func openLock(deadends []string, target string) int {
	for _, deadend := range deadends {
		if deadend == "0000" || deadend == target {
			return -1
		}
	}
	if target == "0000" {
		return 0
	}
	var deadendsMap map[string]bool = make(map[string]bool)
	for _, deadend := range deadends {
		deadendsMap[deadend] = true
	}
	var queue1 []string = make([]string, QUEUE_SIZE)
	var front1 int = 0
	var rear1 int = 0

	var queue2 []string = make([]string, QUEUE_SIZE)
	var front2 int = 0
	var rear2 int = 0

	var visit map[string]bool = make(map[string]bool)
	var ans = 0

	// 0000 inqueue
	queue1[front1] = "0000"
	front1++
	visit["0000"] = true

	for front1 != rear1 {
		// pop
		code := queue1[rear1]
		rear1++

		for i := 0; i < 4; i++ {
			for _, ch := range CHANGE_MAP[[]rune(code)[i]] {
				newCode := replaceAtIndex(code, ch, i)
				if _, ok := deadendsMap[newCode]; ok {
					continue
				}
				if _, ok := visit[newCode]; ok {
					continue
				}
				if newCode == target {
					return ans + 1
				}
				visit[newCode] = true
				queue2[front2] = newCode
				front2++
			}
		}
		if rear1 == front1 {
			queue1 = queue2
			front1 = front2
			rear1 = rear2
			queue2 = make([]string, QUEUE_SIZE)
			front2 = 0
			rear2 = 0
			ans++
			// fmt.Println(queue1[rear1:front1])
		}
	}

	return -1
}

func main() {
	fmt.Println(openLock([]string{"0201", "0101", "0102", "1212", "2002"}, "0202"))
}
