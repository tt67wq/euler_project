/*
 * =====================================================================================
 *
 *       Filename:  enigma2.c
 *
 *    Description:  zoj 1036
 *
 *        Version:  1.0
 *        Created:  2019-08-13
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
#define MAX 1000

char pi0[26];
char pi1[26];
char pi2[26];
char pir[26];
char ip[26];
char plaintext[MAX];
char ciphertext[MAX];

int ks[4];

void shift(char *r, int k) {
        if (k == 0)
                return;
        int i, j;
        char tmp[27];
        memset(tmp, 0, 26 * sizeof(char));
        for (i = 0; i < 26; i++) {
                j = i + k;
                if (j >= 26)
                        j %= 26;
                tmp[i] = r[j];
        }
        tmp[26] = '\0';
        strcpy(r, tmp);
}

void rotor_shift() {
        shift(pi0, ks[0]);
        shift(pi1, ks[1]);
        shift(pi2, ks[2]);
        shift(pir, ks[3]);
}

char reverse(char *r, char s) {
        int i = 0;
        while (i < 26) {
                if (s == r[i])
                        break;
                i++;
        }
        return 'a' + i;
}

void solve() {

        int i, l;
        char *state;
        l = strlen(ciphertext);

        state = (char *)calloc(l, sizeof(char));

        for (i = 0; i < l; i++) {
                /* printf("%s\n", pi0); */
                state[i] = ip[ciphertext[i] - 'a'];
                state[i] = pi0[state[i] - 'a'];
                state[i] = pi1[state[i] - 'a'];
                state[i] = pi2[state[i] - 'a'];
                state[i] = pir[state[i] - 'a'];
                state[i] = reverse(pi2, state[i]);
                state[i] = reverse(pi1, state[i]);
                state[i] = reverse(pi0, state[i]);
                state[i] = reverse(ip, state[i]);

                /* rotate */
                shift(pi0, 1);
                if (i > 0 && i % 26 == 0)
                        shift(pi1, 1);

                if (i > 0 && i % 676 == 0)
                        shift(pi2, 1);

                if (i > 0 && i % 17576 == 0)
                        shift(pir, 1);
        }
        printf("%s\n", state);
        free(state);
}

int main() {
        int n, i;
        scanf("%d", &n);
        getchar();
        while (n-- > 0) {
                for (i = 0; i < 26; i++)
                        pi0[i] = getchar();
                getchar();
                for (i = 0; i < 26; i++)
                        pi1[i] = getchar();
                getchar();
                for (i = 0; i < 26; i++)
                        pi2[i] = getchar();
                getchar();
                for (i = 0; i < 26; i++)
                        pir[i] = getchar();
                getchar();
                for (i = 0; i < 26; i++)
                        ip[i] = getchar();
                getchar();
                for (i = 0; i < 4; i++)
                        ks[i] = getchar() - 'a';

                rotor_shift();

                scanf("%s", plaintext);
                scanf("%s", ciphertext);

                solve();
        }
        return 0;
}
