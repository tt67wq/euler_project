#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Alice 和 Bob 计划分别去罗马开会。

# 给你四个字符串 arriveAlice ，leaveAlice ，arriveBob 和 leaveBob 。Alice 会在日期 arriveAlice 到 leaveAlice 之间在城市里（日期为闭区间），而 Bob 在日期 arriveBob 到 leaveBob 之间在城市里（日期为闭区间）。每个字符串都包含 5 个字符，格式为 "MM-DD" ，对应着一个日期的月和日。

# 请你返回 Alice和 Bob 同时在罗马的天数。

# 你可以假设所有日期都在 同一个 自然年，而且 不是 闰年。每个月份的天数分别为：[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31] 。


# 示例 1：

# 输入：arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
# 输出：3
# 解释：Alice 从 8 月 15 号到 8 月 18 号在罗马。Bob 从 8 月 16 号到 8 月 19 号在罗马，他们同时在罗马的日期为 8 月 16、17 和 18 号。所以答案为 3 。
# 示例 2：

# 输入：arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
# 输出：0
# 解释：Alice 和 Bob 没有同时在罗马的日子，所以我们返回 0 。


# 提示：

# 所有日期的格式均为 "MM-DD" 。
# Alice 和 Bob 的到达日期都 早于或等于 他们的离开日期。
# 题目测试用例所给出的日期均为 非闰年 的有效日期。


class Solution:
    def countDaysTogether(
        self, arriveAlice: str, leaveAlice: str, arriveBob: str, leaveBob: str
    ) -> int:
        if leaveAlice < arriveBob or leaveBob < arriveAlice:
            return 0
        return self.days_between_dates(
            max(arriveAlice, arriveBob), min(leaveAlice, leaveBob)
        )

    def days_between_dates(self, date1: str, date2: str) -> int:
        year_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # 每个月份的天数
        m1, d1 = map(int, date1.split("-"))
        m2, d2 = map(int, date2.split("-"))
        days1 = sum(year_days[: m1 - 1]) + d1  # 计算 date1 在该年中的第几天
        days2 = sum(year_days[: m2 - 1]) + d2  # 计算 date2 在该年中的第几天
        return abs(days2 - days1) + 1  # 计算日期差，并取绝对值


def main():
    print(Solution().countDaysTogether("08-15", "08-18", "08-16", "08-19"))
    print(Solution().countDaysTogether("10-01", "10-31", "11-01", "12-31"))


if __name__ == "__main__":
    main()
