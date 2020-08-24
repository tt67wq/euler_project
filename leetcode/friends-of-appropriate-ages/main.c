/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-24
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

int numFriendRequests(int *ages, int agesSize) {
        int buckets[121] = {0};

        for (int i = 0; i < agesSize; i++) {
                buckets[ages[i]]++;
        }

        int ans = 0;

        // age[B] <= 0.5 * age[A] + 7
        // age[B] > age[A]
        // age[B] > 100 && age[A] < 100

        for (int ageA = 0; ageA < 121; ageA++) {
                int countA = buckets[ageA];
                for (int ageB = 0; ageB < 121; ageB++) {
                        int countB = buckets[ageB];
                        if (ageB <= ageA * 0.5 + 7)
                                continue;

                        if (ageB > ageA)
                                continue;

                        if (ageB > 100 && ageA < 100)
                                continue;

                        ans += countA * countB;
                        if (ageA == ageB) {
                                ans -= countA;
                        }
                }
        }
        return ans;
}

int main() { return 0; }