/*
 * =====================================================================================
 *
 *       Filename:  gn.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int game(int *guess, int guessSize, int *answer, int answerSize) {
        int i, j = 0;
        for (i = 0; i < guessSize; i++) {
                if (guess[i] == answer[i])
                        j++;
        }
        return j;
}

int main() { return 0; }
