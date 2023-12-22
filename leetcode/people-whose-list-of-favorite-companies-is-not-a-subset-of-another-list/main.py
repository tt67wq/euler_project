#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/description/

import unittest
from typing import List


class Solution:
    def peopleIndexes(self, favoriteCompanies: List[List[str]]) -> List[int]:
        n = len(favoriteCompanies)
        compSets = [set(favList) for favList in favoriteCompanies]
        tops = set(range(n))

        for i in range(n):
            if i not in tops:
                continue
            for j in range(i + 1, n):
                if j not in tops:
                    continue
                if i in tops and compSets[i].issubset(compSets[j]):
                    tops.remove(i)
                elif compSets[j].issubset(compSets[i]):
                    tops.remove(j)
        return list(tops)


class TestSolution(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_peopleIndexes(self):
        # Test case 1
        favoriteCompanies1 = [
            ["leetcode", "google", "facebook"],
            ["google", "microsoft"],
            ["google", "facebook"],
            ["google"],
            ["amazon"],
        ]
        expected1 = [0, 1, 4]
        self.assertEqual(self.solution.peopleIndexes(favoriteCompanies1), expected1)

        # Test case 2
        favoriteCompanies2 = [
            ["leetcode", "google", "facebook"],
            ["leetcode", "amazon"],
            ["facebook", "google"],
        ]
        expected2 = [0, 1]
        self.assertEqual(self.solution.peopleIndexes(favoriteCompanies2), expected2)

        # Test case 3
        favoriteCompanies3 = [["leetcode"], ["google"], ["facebook"], ["amazon"]]
        expected3 = [0, 1, 2, 3]
        self.assertEqual(self.solution.peopleIndexes(favoriteCompanies3), expected3)

        # Test case 4
        favoriteCompanies4 = [
            ["leetcode", "google", "facebook"],
            ["google", "microsoft"],
            ["google", "facebook"],
            ["google"],
            ["amazon"],
            ["leetcode", "amazon"],
        ]
        expected4 = [0, 1, 5]
        self.assertEqual(self.solution.peopleIndexes(favoriteCompanies4), expected4)


if __name__ == "__main__":
    unittest.main()
