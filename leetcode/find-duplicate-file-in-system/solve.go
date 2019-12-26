package main

import (
	"fmt"
	"strings"
)

type myfile struct {
	path    string
	name    string
	content string
}

func findDuplicate(paths []string) [][]string {

	var p string
	var items []string
	var fs []*myfile
	var group map[string][]*myfile = make(map[string][]*myfile)
	var ans [][]string = make([][]string, 0)

	for _, p = range paths {
		// parse
		items = strings.Split(p, " ")

		for i := 1; i < len(items); i++ {
			f := new(myfile)
			f.path = items[0]
			tmp := strings.Split(items[i], ".txt")
			f.name = tmp[0] + ".txt"
			f.content = tmp[1][1 : len(tmp[1])-1]
			fs = append(fs, f)
		}
	}

	// group by content
	for _, f := range fs {
		// fmt.Println(f)
		group[f.content] = append(group[f.content], f)
	}

	for _, vs := range group {
		if len(vs) > 1 {
			an := make([]string, 0)
			for _, v := range vs {
				an = append(an, fmt.Sprintf("%s/%s", v.path, v.name))
			}
			ans = append(ans, an)

		}
	}

	return ans
}

func main() {
	for _, ln := range findDuplicate([]string{"root/qgjazhtliq/djmevsktisuvd/acsuolhnermqzok/mkts/ibrdqxawjgut/emb wl.txt(odumfqzwczehoyk) z.txt(gojsklotgchjzfm) txtoyg.txt(gojsklotgchjzfm) eupidhefx.txt(ahlsazuzrsf) rekzkaifwp.txt(yfxaymkefaofowqjpgaceffkjsehtmqkgy) l.txt(odumfqzwczehoyk) bqmhpxumxlbe.txt(yfxaymkefaofowqjpgaceffkjsehtmqkgy) qoqgiauqbayuc.txt(odumfqzwczehoyk) mpstemqlxy.txt(ahlsazuzrsf)"}) {
		fmt.Println(ln)
	}
}
