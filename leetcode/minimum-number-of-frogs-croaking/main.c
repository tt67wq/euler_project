/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-11
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
#define MAX 1000

int minNumberOfFrogs(char *croakOfFrogs) {
        int hash[26] = {0};
        int min = 0;
        for (int i = 0; croakOfFrogs[i] != '\0'; ++i) {
                hash[croakOfFrogs[i] - 'a'] += 1;
                if (!(hash['c' - 'a'] >= hash['r' - 'a'] && hash['r' - 'a'] >= hash['o' - 'a'] &&
                      hash['o' - 'a'] >= hash['a' - 'a'] && hash['a' - 'a'] >= hash['k' - 'a']))
                        return -1;
                if (hash['c' - 'a'] && hash['r' - 'a'] && hash['o' - 'a'] && hash['a' - 'a'] &&
                    hash['k' - 'a']) {
                        min = min > hash['c' - 'a'] ? min : hash['c' - 'a'];
                        hash['c' - 'a'] -= 1;
                        hash['r' - 'a'] -= 1;
                        hash['o' - 'a'] -= 1;
                        hash['a' - 'a'] -= 1;
                        hash['k' - 'a'] -= 1;
                }
        }
        return hash['c' - 'a'] || hash['r' - 'a'] || hash['o' - 'a'] || hash['a' - 'a'] ||
                       hash['k' - 'a']
                   ? -1
                   : min;
}

int main() {
        printf("%d\n", minNumberOfFrogs("croakcroak"));
        printf("%d\n", minNumberOfFrogs("crcoakroak"));

        return 0;
}
