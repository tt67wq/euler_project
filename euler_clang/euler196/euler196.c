/*
 * =====================================================================================
 *
 *       Filename:  euler196.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[]) {
        uint64_t s = 0;
        int level = 0;
        level = atoi(argv[1]);
        for (int i = 1; i <= level; i++)
                s += i;
        printf("%llu\n", s);
        return 0;
}
