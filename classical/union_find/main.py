#!/usr/bin/env python
# -*- coding: utf-8 -*-


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, p):
        while p != self.parent[p]:
            self.parent[p] = self.parent[self.parent[p]]  # 路径压缩
            p = self.parent[p]
        return p

    def union(self, p, q):
        i = self.find(p)
        j = self.find(q)
        if i == j:
            return
        if self.rank[i] > self.rank[j]:
            self.parent[j] = i
        else:
            self.parent[i] = j
            if self.rank[i] == self.rank[j]:
                self.rank[j] += 1


class TestUnionFind:
    def test_find(self):
        uf = UnionFind(5)
        uf.union(0, 1)
        uf.union(1, 2)
        assert uf.find(0) == uf.find(2)
        assert uf.find(0) != uf.find(4)

    def test_union(self):
        uf = UnionFind(5)
        uf.union(0, 1)
        uf.union(1, 2)
        uf.union(3, 4)
        assert uf.find(0) == uf.find(2)
        assert uf.find(3) == uf.find(4)
        assert uf.find(0) != uf.find(4)


def main():
    TestUnionFind().test_find()
    TestUnionFind().test_union()


if __name__ == "__main__":
    main()
