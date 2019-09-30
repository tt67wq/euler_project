#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


import sxtwl
import sys
import datetime

Gan = ["甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"]
Zhi = ["子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"]
ShX = ["鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"]
numCn = ["零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十"]
Week = ["日", "一", "二", "三", "四", "五", "六"]
jqmc = ["冬至", "小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种",
        "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪"]
ymc = ["十一", "十二", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十"]
rmc = ["初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五",
       "十六", "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十", "卅一"]

# 打印做一个中间转换


def print_day(day):
    print("===================================================")
    print("公历:", day.y, "年", day.m, "月", day.d, "日")
    if day.Lleap:
        print("润", (day.Lyear0 + 1984), "年", ymc[day.Lmc], "月", rmc[day.Ldi], "日")
    else:
        print((day.Lyear0 + 1984), "年", ymc[day.Lmc], "月", rmc[day.Ldi], "日")

    if (day.qk >= 0):
        print("当日节气:" + jqmc[day.jqmc])
        print("节气时间:" + day.jqsj)

    print("儒略日:JD", sxtwl.J2000 + day.d0)
    print("星期", Week[day.week])

    print(Gan[day.Lyear2.tg], Zhi[day.Lyear2.dz], "年")
    print(Gan[day.Lmonth2.tg], Zhi[day.Lmonth2.dz], "月")
    print(Gan[day.Lday2.tg], Zhi[day.Lday2.dz], "日")

    print("距冬至", day.cur_dz, "天")
    print("距夏至", day.cur_xz, "天")
    print("距立秋", day.cur_lq, "天")
    print("距芒种", day.cur_mz, "天")
    print("距小暑", day.cur_xs, "天")


def get_today():
    lunar = sxtwl.Lunar()
    a = datetime.datetime.now()
    return lunar.getDayBySolar(a.year, a.month, a.day)


def main():
    lunar = sxtwl.Lunar()

    # 获取某个阳历日的信息(可在信息中查询到阴历，天干等)
    day = lunar.getDayBySolar(2019, 9, 30)
    print_day(day)

    # 获取某个阴历日的信息(可在信息中查询到阳历，天干等)
    # day2 = lunar.getDayByLunar(2019, 9, 30)
    # print_day(day2)

    # 获取时辰上的那个天干(例如拿下午13点的时辰干支)
    # gz = lunar.getShiGz(day.Lday2.tg, 13)
    # print("获取时辰的干支:" + Gan[gz.tg] + Zhi[gz.dz])

    # print("===================================================")
    # # 获取一年的信息(干支，生肖，)
    # year = lunar.getYearCal(2018)
    # print("获取年的干支:" + Gan[year.yearGan] + Zhi[year.yearZhi])
    # print("获取年的生肖:" + ShX[year.ShX])


if __name__ == '__main__':
    main()
