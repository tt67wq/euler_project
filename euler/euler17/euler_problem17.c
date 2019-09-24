/*
 * =====================================================================================
 *
 *       Filename:  euler_problem17.c
 *
 *    Description:  欧拉计划17题
 *
 *        Version:  1.0
 *        Created:  2018-07-27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *nums[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *nums2[19] = {"one",     "two",       "three",    "four",     "five",
                   "six",     "seven",     "eight",    "nine",     "ten",
                   "eleven",  "twelve",    "thirteen", "fourteen", "fifteen",
                   "sixteen", "seventeen", "eighteen", "nineteen"};
char *nums3[8] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

char *join(char *s1, char *s2) {
        char *result = malloc(strlen(s1) + strlen(s2) + 1); 
        if (result == NULL)
                exit(1);

        strcpy(result, s1);
        strcat(result, s2);

        return result;
}

void integer_to_words(int num, char **words) {
        char *ts, *hs, *rs;
        int t = num / 1000;
        if (t > 0) {
                ts = join(nums[t - 1], "thousand");
        } else {
                ts = "";
        }
        int h = num % 1000 / 100;
        if (h > 0) {
                hs = join(nums[h - 1], "hundred");
        } else {
                hs = "";
        }
        *words = join(ts, hs);
        int r = num % 100;
        if (r < 20) {
                if (r == 0)
                        rs = "";
                else
                        rs = nums2[r - 1];
        } else {
                if (num % 10 == 0)
                        rs = nums3[num % 100 / 10 - 2];
                else
                        rs = join(nums3[num % 100 / 10 - 2], nums[r % 10 - 1]);
        }
        if (r > 0 && strlen(*words) > 0)
                *words = join(*words, "and");
        *words = join(*words, rs);
}

int main() {
        clock_t begin = clock();

        int l = 0;
        for (int i = 1; i <= 1000; i++) {
                char *words = "";
                integer_to_words(i, &words);
                /* printf("%d ==> %s\n", i, words); */
                l += strlen(words);
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d, time use => %lfs\n", l, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
