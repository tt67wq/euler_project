/*
 * =====================================================================================
 *
 *       Filename:  enigma.c
 *
 *    Description:  zoj 1009
 *
 *        Version:  1.0
 *        Created:  2019-07-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rotor_len, n;
char base[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotor0[26];
char rotor1[26];
char rotor2[26];
int shift0[26];
int shift1[26];
int shift2[26];

char crypto[1000][200];

void gen_shift(char *rotor, int *shift) {
        int i;
        for (i = 0; i < rotor_len; i++)
                if (rotor[i] - base[i] >= 0)
                        shift[i] = rotor[i] - base[i];
                else
                        shift[i] = rotor_len + rotor[i] - base[i];
}

void decode(char *crypto) {
        int i, j, len, tmp;
        len = strlen(crypto);
        i = 0;

	char _rotor0[26];
	char _rotor1[26];
	char _rotor2[26];

	strcpy(_rotor0, rotor0);
	strcpy(_rotor1, rotor1);
	strcpy(_rotor2, rotor2);
	
        while (i < len) {
                for (j = 0; j < rotor_len; j++) {
                        if (crypto[i] == _rotor2[j]) {
                                crypto[i] = base[j];
                                break;
                        }
                }
                for (j = 0; j < rotor_len; j++) {
                        if (crypto[i] == _rotor1[j]) {
                                crypto[i] = base[j];
                                break;
                        }
                }
                for (j = 0; j < rotor_len; j++) {
                        if (crypto[i] == _rotor0[j]) {
                                crypto[i] = base[j];
                                break;
                        }
                }

                i++;
                for (j = 0; j < rotor_len; j++) {
                        tmp = j - i;
                        while (tmp < 0)
                                tmp += rotor_len;

                        _rotor0[j] = base[(j + shift0[tmp]) % rotor_len];
                }
                if (i % rotor_len == 0) {
                        for (j = 0; j < rotor_len; j++) {
                                tmp = j - i / rotor_len;
                                while (tmp < 0)
                                        tmp += rotor_len;

                                _rotor1[j] = base[(j + shift1[tmp]) % rotor_len];
                        }
                }
                if (i % (rotor_len * rotor_len) == 0) {
                        for (j = 0; j < rotor_len; j++) {
                                tmp = j - i / (rotor_len * rotor_len);
                                while (tmp < 0)
                                        tmp += rotor_len;

                                _rotor2[j] = base[(j + shift2[tmp]) % rotor_len];
                        }
                }
        }
        for (i = 0; i < len; i++)
                crypto[i] = tolower(crypto[i]);
}

int main() {
        int i, index = 1;

        while (scanf("%d", &rotor_len) != EOF) {
                if (!rotor_len)
                        break;
                if (index != 1)
                        printf("\n");
                printf("Enigma %d:\n", index++);

                scanf("%s", rotor0);
                scanf("%s", rotor1);
                scanf("%s", rotor2);

                gen_shift(rotor0, shift0);
                gen_shift(rotor1, shift1);
                gen_shift(rotor2, shift2);

                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                        scanf("%s", crypto[i]);
                        decode(crypto[i]);
                        printf("%s\n", crypto[i]);
                }
        }

        return 0;
}
