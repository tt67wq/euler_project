package main

import (
	"fmt"
)

func simplifyPath(path string) string {
	var stack []string
	var buffer []byte
	var i, l int
	var ans string

	l = len(path)
	i = 0
	buffer = make([]byte, 0)
	stack = make([]string, 0)

	for i < l+1 {
		if i < l && path[i] != '/' {
			buffer = append(buffer, path[i])
			i++
			continue
		}

		if string(buffer) == "." || string(buffer) == "" {
			// do nothing
			buffer = make([]byte, 0)
			i++
			continue
		}

		if string(buffer) == ".." {
			if len(stack) > 0 {
				// pop
				stack = stack[:len(stack)-1]
			}
			buffer = make([]byte, 0)
			i++
			continue
		}

		// push
		stack = append(stack, string(buffer))
		buffer = make([]byte, 0)
		i++
	}

	ans = "/"

	for _, item := range stack {
		ans += item
		ans += "/"
	}

	if ans == "/" {
		return ans
	}

	return ans[:len(ans)-1]
}

func main() {
	fmt.Println(simplifyPath("/a/../../b/../c//.//"))
	fmt.Println(simplifyPath("/a//b////c/d//././/.."))
	fmt.Println(simplifyPath("/home//foo/"))
}
