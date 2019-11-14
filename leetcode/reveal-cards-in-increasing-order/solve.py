class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        # 反向收牌
        # 1、deck数组降序排序，并将最大值给result数组
        # 2、将底部的牌放到顶部
        # 3、新加一张牌到顶部
        # 4、重复2、3直到所有牌都加进来
        deck.sort(reverse=True)
        result = [deck[0]]
        for i in range(1, len(deck)):
            base = result[-1]
            del result[-1]
            result.insert(0, base)
            result.insert(0, deck[i])
        return result
