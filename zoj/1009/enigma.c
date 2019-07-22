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

char crypto[10][BUFSIZ];

void gen_shift(char *rotor, int *shift) {
        int i;
        for (i = 0; i < rotor_len; i++)
                shift[i] = base[i] - rotor[i];
}

void decode(char *crypto) {
        int i, j;
        int len;
        len = strlen(crypto);
        for (i = 0; i < len; i++) {
                for (j = 0; j < 26; j++) {
                        if (base[j] + shift2[i] == crypto[i]) {
                                crypto[i] = base[j];
                                break;
                        }
                }
                for (j = 0; j < 26; j++) {
                        if (base[j] + shift1[i] == crypto[i]) {
                                crypto[i] = base[j];
                                break;
                        }
                }

                for (j = 0; j < 26; j++) {
                        if (base[j] + shift0[i] == crypto[i]) {
                                crypto[i] = base[j];
                                break;
                        }
                }

                /* shift */
                for (j = 0; j < rotor_len; j++) {
                        shift0[(j + 1) % rotor_len] = shift0[j];
                        if (i % rotor_len == 0)
                                shift1[(j + 1) % rotor_len] = shift1[j];
                        if (i % (rotor_len * rotor_len) == 0)
                                shift2[(j + 1) % rotor_len] = shift2[j];
                }
        }
}

int main() {
        int i, index = 1;

        while (scanf("%d", &rotor_len) != EOF) {
                if (!rotor_len)
                        break;
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
                }
                printf("Enigma %d:\n", index);
                for (i = 0; i < n; i++) {
                        printf("%s\n", crypto[i]);
                }
                printf("\n");
        }

        return 0;
}
