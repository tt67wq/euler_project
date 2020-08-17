/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-17
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

int minRefuelStops(int target, int startFuel, int **stations, int stationsSize,
                   int *stationsColSize) {
        if (startFuel >= target) {
                return 0;
        }

        if (startFuel < target && stationsSize == 0) {
                return -1;
        }

        int maxDis = startFuel;

        int maxGas = 0, count = 0, alreadyReach = 0;

        while (maxDis < target) {
                for (int i = 0; i < stationsSize && stations[i][0] <= maxDis; i++) {
                        if (stations[i][1] > maxGas) {
                                maxGas = stations[i][1];
                                alreadyReach = i;
                        }
                }
                stations[alreadyReach][1] = 0;
                if (maxGas == 0) {
                        return -1;
                }
                maxDis += maxGas;
                count++;
                maxGas = 0;
        }
        return count;
}

int main() { return 0; }