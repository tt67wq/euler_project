#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "欧拉计划67题"

LIMIT = 99


def bfs(triangle, i, j, cache):
    if i == LIMIT:
        return triangle[i][j]
    # search cache
    if cache.get("{},{}".format(i, j)):
        return cache["{},{}".format(i, j)]

    # cache not hit
    # search left and right
    lmax = bfs(triangle, i+1, j, cache)
    rmax = bfs(triangle, i+1, j+1, cache)
    v = max(lmax, rmax) + triangle[i][j]
    # cache it
    cache["{},{}".format(i, j)] = v
    return v


def main():
    tr = []
    with open("p067_triangle.txt", "r") as f:
        for line in f.readlines():
            tr.append([int(elem) for elem in line.strip().split(" ")])
    print(bfs(tr, 0, 0, {}))


if __name__ == '__main__':
    main()
