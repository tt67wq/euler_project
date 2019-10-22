#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "马拉车算法求回文字串"

def manacher(cs):
    s = '#' + '#'.join(cs) + '#'
    lens = len(s)
    p = [0] * lens
    mx = 0
    id = 0
    for i in range(lens):
        if mx > i:
            p[i] = min(mx-i, p[int(2*id-i)])
        else:
            p[i] = 1
        while i-p[i] >= 0 and i+p[i] < lens and s[i-p[i]] == s[i+p[i]]:
            p[i] += 1
        if(i+p[i]) > mx:
            mx, id = i+p[i], i

    counter = 0
    for i in range(len(p)):
        if(p[i]-1 > 1):
            ps = s[i-(p[i]-1):i+p[i]]
            print(ps.replace('#', ''), p[i]-1)
            counter += 1
    return counter


def main():
    manacher("agfhiialblajhqwjhek")
    # ii 2
    # albla 5



if __name__ == '__main__':
    main()
