#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class ZhouYi:
    """
    周易卦数：乾一；兑二；离三；震四；巽五；坎六；艮七；坤八。

    五行生克：金生水，水生木，木生火，火生土，土生金；金克木，木克土，土克水，水克火，火克金。

    八宫所属五行：乾、兑→金；坤、艮→土；震、巽→木；坎→水；离→火。

    卦气旺：震、巽木旺于春，离火旺于夏，乾、兑金旺于秋，坎水旺于冬，坤、艮土旺于辰戌丑未月。

    卦气衰：春坤、艮，夏乾、兑，秋震、巽，冬离，辰戌丑未坎。

    十天干：甲乙东方木，丙丁南方火，戊己中央土，庚辛西方金，壬癸北方水。

    十二地支：子水鼠，丑土牛，寅木虎，卯木兔，辰土龙，巳火蛇，午火马，未土羊，申猴金，酉金鸡，戌土犬，亥水猪。

    八卦象例：乾三连，坤六断，震仰盂，艮覆碗，离中虚，坎中满，兑上缺，巽下断。
    """
    GuaMap = {
        "乾": {"卦数": 1, "五行": "金", "旺": "秋", "衰": "夏", "象例": "三连"},
        "兑": {"卦数": 2, "五行": "金", "旺": "秋", "衰": "夏", "象例": "上缺"},
        "离": {"卦数": 3, "五行": "火", "旺": "夏", "衰": "冬", "象例": "中虚"},
        "震": {"卦数": 4, "五行": "木", "旺": "春", "衰": "秋", "象例": "仰盂"},
        "巽": {"卦数": 5, "五行": "木", "旺": "春", "衰": "秋", "象例": "下断"},
        "坎": {"卦数": 6, "五行": "水", "旺": "冬", "衰": "辰戌丑未", "象例": "中满"},
        "艮": {"卦数": 7, "五行": "土", "旺": "辰戌丑未", "衰": "春", "象例": "覆碗"},
        "坤": {"卦数": 8, "五行": "土", "旺": "辰戌丑未", "衰": "春", "象例": "六断"}
    }
    WuXing = {
        "金": {"生": "水", "克": "木", "被生": "土", "被克": "火", "天干": "庚辛西方", "地支": ["申金", "酉鸡"]},
        "木": {"生": "火", "克": "土", "被生": "土", "被克": "金", "天干": "甲乙东方", "地支": ["寅虎", "卯兔"]},
        "水": {"生": "木", "克": "火", "被生": "金", "被克": "土", "天干": "壬癸北方", "地支": ["子鼠", "亥猪"]},
        "火": {"生": "土", "克": "金", "被生": "木", "被克": "水", "天干": "丙丁南方", "地支": ["巳蛇", "午马"]},
        "土": {"生": "金", "克": "水", "被生": "火", "被克": "木", "天干": "戊己中央", "地支": ["丑牛", "辰龙", "未羊", "戌犬"]},
    }
    Gua = ["乾", "兑", "离", "震", "巽", "坎", "艮", "坤"]
    Gan = ["甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"]
    Zhi = ["子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"]
    ShX = ["鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"]
    Ymc = ["十一", "十二", "正", "二", "三", "四", "五", "六", "七", "八", "九", "十"]
    Rmc = ["初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五",
           "十六", "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十", "卅一"]


def main():
    pass


if __name__ == '__main__':
    main()