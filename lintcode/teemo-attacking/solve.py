#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    """
    @param timeSeries: the Teemo's attacking ascending time series towards Ashe
    @param duration: the poisoning time duration per Teemo's attacking
    @return: the total time that Ashe is in poisoned condition
    """

    def findPoisonedDuration(self, timeSeries, duration):
        # Write your code here
        if len(timeSeries) == 0:
            return 0
        if len(timeSeries) == 1:
            return duration

        idx = 0
        ans = 0
        for ts in timeSeries:
            if idx < ts:
                ans += duration
            else:
                if idx - ts > duration:
                    pass
                else:
                    ans += duration - (idx - ts) - 1

            idx = ts + duration - 1

        return ans


def main():
    s = Solution()
    print(s.findPoisonedDuration([1, 4], 2))


if __name__ == '__main__':
    main()
