/* 欧拉计划第126题，用elixir实在是不好写了，改用c写 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20000

int f(int t, int x, int y, int z) { return 4 * (t - 1) * (x + y + z + t - 2) + 2 * (x * y + y * z + x * z); }

int main(void) {
        int cache[100000];

        for (int x = 1; f(1, x, x, x) <= MAX; x++)
                for (int y = x; f(1, x, y, y) <= MAX; y++)
                        for (int z = y; f(1, x, y, z) <= MAX; z++)
                                for (int t = 1; f(t, x, y, z) <= MAX; t++)
                                        cache[f(t, x, y, z)]++;

        for (int i = 1; i <= 100000; i++)
                if (cache[i] == 1000)
                        printf("%d %d\n", i, cache[i]);

        return EXIT_SUCCESS;
}
