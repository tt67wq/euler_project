#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""
import hashlib
import copy

queue = []
cache = {}


def all_equal(bs):
    t = bs[0]
    for e in bs:
        if e != t:
            return 0
    return 1


def copy_one(origin):
    return copy.deepcopy(origin)


def find_max_min(bs):
    max = 0
    max_index = 0
    min = 0
    min_index = 0
    for i, e in enumerate(bs):
        if e > max:
            max = e
            max_index = i
        if e < min:
            min = e
            min_index = i
    return max_index, min_index


def fp(bs):
    m = hashlib.md5()
    m.update(",".join([str(e) for e in bs]).encode())
    return m.hexdigest()


def bfs():
    global queue
    global cache

    step = 0
    while(len(queue) > 0):
        head = queue.pop()
        # print(head, queue)
        if all_equal(head["bs"]):
            step = head["step"]
            break

        i, j = find_max_min(head["bs"])
        head["bs"][i] -= 1

        # remove
        child = copy_one(head)
        if not cache.get(fp(child["bs"])):
            child["step"] += 1
            queue.insert(0, child)
            cache[fp(child["bs"])] = 1

        # move from i to j
        child = copy_one(head)
        child["bs"][j] += 1
        if not cache.get(fp(child["bs"])):
            child["step"] += 1
            queue.insert(0, child)
            cache[fp(child["bs"])] = 1

    return step


def main():
    c = int(input())
    while c > 0:
        global queue
        global cache
        queue = []
        cache = {}
        n = int(input())
        bs = [int(i) for i in input().split(' ')]
        cache[fp(bs)] = 1
        queue.insert(0, {"bs": bs, "step": 0, "size": n})
        print(bfs())
        c -= 1


if __name__ == '__main__':
    main()
