/*
 * =====================================================================================
 *
 *       Filename:  untwist.c
 *
 *    Description:  zoj 1006
 *
 *        Version:  1.0
 *        Created:  2019-07-15
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

#define MAX 100

int len;
int k;
char pt[MAX];
char ct[MAX];
char cc[MAX];
char pc[MAX];

char letter2code(char letter) {
        if (letter == '_')
                return 0;
        if (letter == '.')
                return 27;
        return letter - 'a' + 1;
}

char code2letter(char code) {
        if (code == 0)
                return '_';
        if (code == 27)
                return '.';
        return code - 1 + 'a';
}

void c2p() {
        int i, tmp;
        for (i = 0; i < len; i++) {
                tmp = cc[i] + i;
                pc[k * i % len] = tmp > 27 ? tmp % 28 : tmp;
        }
}

void init() {
        int i;
        for (i = 0; i < MAX; i++) {
                cc[i] = 0;
                pc[i] = 0;
                pt[i] = 0;
        }
}

int main() {

        int i;
        while (scanf("%d", &k) != EOF) {
                if (!k)
                        break;
                scanf("%s", ct);
                len = strlen(ct);

                init();

                for (i = 0; i < len; i++)
                        cc[i] = letter2code(ct[i]);
                c2p();

                for (i = 0; i < len; i++)
                        printf("%c", code2letter(pc[i]));
                printf("\n");
        }
        return 0;
}
