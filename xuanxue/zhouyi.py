#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "周易基础"
import datetime
import sxtwl
from config import ZhouYi


def gua_by_time():
    """
    年月日时起卦例子：
    年月日为上卦。年月日加时总数为下卦。又以年月日时总数取爻。
    如子年一数，丑年二数，直至亥年十二数。
    月如正月一数，直至十二月，亦作十二数。
    日数如初一一数，直至三十日，为三十数。
    以上年月日共计几数，以八除之，以余数作卦。
    如子时一数直至亥时十二数，就将年月日数加时之数，总计几数，以八除之，余数作下卦；以六除，余数作动爻。
    """
    lunar = sxtwl.Lunar()
    a = datetime.datetime.now()
    day = lunar.getDayBySolar(a.year, a.month, a.day)
    y = day.Lyear2.dz+1
    m = day.Lmc-1
    d = day.Ldi+1
    h = a.hour//2+1

    shang_gua = (y+m+d) % 8
    xia_gua = (y+m+d+h) % 8
    yao = (y+m+d+h) % 6
    return {
        "上卦": ZhouYi.Gua[shang_gua-1],
        "下卦": ZhouYi.Gua[xia_gua-1],
        "动爻": yao
    }


def gua_by_num(n):
    """
    物数占例凡见有可数之物，即以此数起作上卦，以时数配作下卦。
    即以卦数并时数总除六取动爻。
    """
    h = datetime.datetime.now().hour//2+1
    return {
        "上卦": ZhouYi.Gua[n % 8-1],
        "下卦": ZhouYi.Gua[h % 8-1],
        "动爻": (h+n) % 6
    }


def main():
    pass


if __name__ == '__main__':
    main()
