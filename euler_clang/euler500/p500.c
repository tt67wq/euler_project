/*
 * =====================================================================================
 *
 *       Filename:  p500.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000L
#define MAXN 10
#define TARGET 4

char sieve[MAX / 16 + 1];
long heap[MAXN];
int vis[MAXN];

static inline bool is_in_sieve(long idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
        long i, j;
        for (i = 3; i * i <= MAX; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
}

int min_index() {
        int i, mi;
        long min, tmp;

        min = heap[0];
        mi = 0;
        for (i = 1; i < MAXN; i++) {
                tmp = heap[i];
                if (tmp < min) {
                        min = tmp;
                        mi = i;
                }
        }
        return mi;
}

void solve() {
        int mi;
        int total = TARGET;
        long tmp;

        while (total > 0) {
                mi = min_index();
                tmp = heap[mi];
                heap[mi] = tmp * tmp;
                vis[mi]++;
                total--;
        }
}

int main() {
        long i, count = 0;
        init();
        prime_sieve();

        bzero(heap, sizeof(long) * MAXN);
        bzero(vis, sizeof(int) * MAXN);

        heap[count] = 2;
        for (i = 3; i < MAX && count < MAXN; i++) {
                if (is_in_sieve(i)) {
                        count += 1;
                        heap[count] = i;
                }
        }
        solve();
        for (i = 0; i < MAXN; i++) {
                printf("vis[%ld] = %d\n", i, vis[i]);
        }
        return 0;
}
