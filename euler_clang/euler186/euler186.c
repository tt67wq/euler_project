/*
 * =====================================================================================
 *
 *       Filename:  euler186.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000
#define Minister 524287
#define TARGET 4651264 // number of calls, including misdials, is TARGET/2
char BOOL[N] = {0};
int Users[N][20] = {0};

int main(void) {
        clock_t start, end;
        start = clock();
        int *S = malloc(sizeof(int) * (TARGET + 1));
        int misdial = 0, k, i, j, tmp1, tmp2, lmt;
        long long int p;

        for (p = 1; p <= 55; p++) {
                S[p] = (int)((100003 - 200003 * p + 300007 * p * p * p) % N);
        }
        for (k = 56; k <= TARGET; k++) {
                S[k] = (S[k - 24] + S[k - 55]) % N;
        }

        for (k = 1; k < TARGET; k += 2) {
                tmp1 = S[k];
                tmp2 = S[k + 1];
                if (tmp1 == tmp2) {
                        misdial++;
                        continue;
                }
                lmt = Users[tmp1][0];
                for (i = 1; i <= lmt; i++) {
                        if (Users[tmp1][i] == tmp2)
                                goto label;
                }
                Users[tmp1][++Users[tmp1][0]] = tmp2;
                Users[tmp2][++Users[tmp2][0]] = tmp1;
        label:;
        }
        free(S);

        int *H = malloc(sizeof(int) * N);
        H[0] = Minister;
        BOOL[Minister] = 1;
        j = 1;

        for (i = 0; i < j; i++) {
                lmt = Users[H[i]][0];
                for (k = 1; k <= lmt; k++) {
                        if (BOOL[Users[H[i]][k]])
                                continue;
                        BOOL[H[j++] = Users[H[i]][k]] = 1;
                }
        }
        free(H);

        int solution = 0;
        for (i = 0; i < N; i++)
                if (BOOL[i])
                        solution++;
        end = clock();
        double sec = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Number of vertices in Minister's connected component is %d.\n"
               "Number of successful calls is %d, of which %d misdials.\n"
               "Time elapsed: %.3fs\n",
               solution, (TARGET / 2) - misdial, misdial, sec);
        return 0;
}
