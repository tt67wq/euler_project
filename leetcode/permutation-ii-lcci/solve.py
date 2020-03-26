#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution(object):
    def permutation(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        # nums.sort() # 数组先排序
        S = "".join((lambda x: (x.sort(), x)[1])(list(S)))  ###字符串排序,相同的在一起（排序去重）

        def backtrack(nums, list_one):
            if not nums:
                res.append(list_one[:])  #####切记 [:]
                return
            for i in range(len(nums)):
                if i > 0 and nums[i] == nums[i - 1]:
                    continue  # 每当进入新的构成，先考虑该构成的首字符是否和上一个一样。
                list_one += nums[i]
                backtrack(
                    nums[:i] + nums[i + 1 :], list_one
                )  # nums[:i]+nums[i+1:] 避免了重复利用。
                list_one = list_one[:-1]

        res = []
        list_one = ""
        backtrack(S, list_one)
        return res


def main():
    s = Solution()
    print(s.permutation("abb"))


if __name__ == "__main__":
    main()
