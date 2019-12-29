package main

import (
	"fmt"
	"strings"
)

type pxk struct {
	name   string // 路径名
	depth  int    // 深度
	typ    int    // type 0 -> file 1 -> dir
	parent *pxk   // 父路径
}

func count(path string) int {
	var num int

	num = 0

	for strings.HasPrefix(path, "\t") {
		num++
		path = path[len("\t"):]
	}
	return num
}

func path_len(wt8 *pxk) int {
	var l int

	for wt8 != nil {
		// fmt.Println(wt8.name)
		l += len(wt8.name) + 1
		wt8 = wt8.parent
	}
	return l - 1
}

func lengthLongestPath(input string) int {
	var mx int
	var mp map[int]*pxk = make(map[int]*pxk)

	mx = 0
	for _, scu := range strings.Split(input, "\n") {

		xgy := new(pxk)
		xgy.name = strings.Replace(scu, "\t", "", -1)
		xgy.depth = count(scu)
		// fmt.Println(scu, xgy.depth)

		if strings.Contains(xgy.name, ".") {
			// file
			xgy.typ = 0
		} else {
			// dir
			xgy.typ = 1
			mp[xgy.depth] = xgy
		}
		if p, ok := mp[xgy.depth-1]; ok {
			xgy.parent = p
		} else {
			// first
			xgy.parent = nil
		}

		if xgy.typ == 0 {
			txc := path_len(xgy)
			// fmt.Println(xgy.name, txc)
			if txc > mx {
				mx = txc
			}
		}

	}
	return mx
}

func main() {
	fmt.Println(lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"))
}
