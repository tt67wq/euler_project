/*
 * =====================================================================================
 *
 *       Filename:  fire_net.c
 *
 *    Description:  http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1002
 *
 *        Version:  1.0
 *        Created:  2019-07-09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

int cancel_nums(int pos, int l, char *city) {
         /* calculate how many box will be canceled if we set a blockhouses here */
        int cancel = 0;
        int j = 0;
        // up
        for (j = pos - l; j >= 0; j -= l) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        cancel++;
        }
        // down
        for (j = pos + l; j < l * l; j += l) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        cancel++;
        }

        int t = l * (pos / l);
        // left
        for (j = pos - 1; j >= t; j--) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        cancel++;
        }
        // right
        for (j = pos + 1; j <= t + l - 1; j++) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        cancel++;
        }
        return cancel;
}

void side_affect(int pos, int l, char *city) {
        int j = 0;
        // up
        for (j = pos - l; j >= 0; j -= l) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        city[j] = 3;
        }
        // down
        for (j = pos + l; j < l * l; j += l) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        city[j] = 3;
        }
        int t = l * (pos / l);
        // left
        for (j = pos - 1; j >= t; j--) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        city[j] = 3;
        }
        // right
        for (j = pos + 1; j <= t + l - 1; j++) {
                if (city[j] == 1) // hit a wall
                        break;
                if (city[j] == 0)
                        city[j] = 3;
        }
}

void calculate(int l, char *city, int *counter) {
        // find a pos that cancel least
        int cancel = 0, min_cancel = l * l;
        int i, choose = l * l;
        for (i = 0; i < l * l; i++) {
                if (city[i] == 0) {
                        cancel = cancel_nums(i, l, city);
                        if (cancel < min_cancel) {
                                min_cancel = cancel;
                                choose = i;
                        }
                }
        }
        if (choose == l * l) // full
                return;
        /* printf("position %d choosed, cancel %d blocks\n", choose, cancel); */
        // set choose a blockhouses
        city[choose] = 2;
        // side affect
        side_affect(choose, l, city);
        (*counter)++;
        calculate(l, city, counter);
}

int main() {
        int l = 0, index = 0, i, j, counter;
        int counters[1000] = {0};
        while (scanf("%d", &l) != EOF) {
                if (l > MAX) {
                        printf("too large");
                        continue;
                }
                if (!l)
                        break;

                char *city = (char *)calloc(l * l, sizeof(char));
                for (i = 0; i < l; i++) {
                        // pass
                        char *line = (char *)calloc(l, sizeof(char));
                        scanf("%s", line);
                        for (j = 0; j < l; j++) {
                                city[i * l + j] = line[j] == '.' ? 0 : 1;
                        }
                        free(line);
                }
                // city got find the maximum number of blockhouses
                counter = 0;
                calculate(l, city, &counter);
                // printf("%d\n", counter);
                counters[index++] = counter;
                // free memory
                free(city);
        }
        for (i = 0; i < index; i++)
                printf("%d\n", counters[i]);

        return 0;
}
