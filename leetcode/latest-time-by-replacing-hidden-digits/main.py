#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/latest-time-by-replacing-hidden-digits/

# 给你一个字符串 time ，格式为  hh:mm（小时：分钟），其中某几位数字被隐藏（用 ? 表示）。
# 有效的时间为 00:00 到 23:59 之间的所有时间，包括 00:00 和 23:59 。
# 替换 time 中隐藏的数字，返回你可以得到的最晚有效时间。

# 示例 1：

# 输入：time = "2?:?0"
# 输出："23:50"
# 解释：以数字 '2' 开头的最晚一小时是 23 ，以 '0' 结尾的最晚一分钟是 50 。
# 示例 2：

# 输入：time = "0?:3?"
# 输出："09:39"
# 示例 3：

# 输入：time = "1?:22"
# 输出："19:22"


class Solution:
    def maximumTime(self, time: str) -> str:
        for i, v in enumerate(time):
            if v == "?":
                if i == 0:
                    if time[1] == "?" or int(time[1]) < 4:
                        time = "2" + time[1:]
                    else:
                        time = "1" + time[1:]
                elif i == 1:
                    if time[0] == "2":
                        time = time[0] + "3" + time[2:]
                    else:
                        time = time[0] + "9" + time[2:]
                elif i == 3:
                    time = time[:3] + "5" + time[4:]
                elif i == 4:
                    time = time[:4] + "9"
        return time


def main():
    pass


if __name__ == "__main__":
    main()
