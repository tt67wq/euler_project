
/*
 * =====================================================================================
 *
 *       Filename:  euler_problem22.c
 *
 *    Description:  欧拉计划22题
 *
 *        Version:  1.0
 *        Created:  2018-08-07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 字母序比较
int alphabetical_cmp(char *w1, char *w2) {
        int ml = strlen(w1) > strlen(w2) ? strlen(w1) : strlen(w2);
        for (int i = 0; i < ml; i++) {
                if (w1[i] > w2[i])
                        return 1;
                else if (w1[i] < w2[i])
                        return 0;
                else
                        continue;
        }
        return 0;
}

// 排序
void sort(char **ss, int size) {
        for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                        if (alphabetical_cmp(ss[i], ss[j])) {
                                char *tmp = ss[i];
                                ss[i] = ss[j];
                                ss[j] = tmp;
                        }
                }
        }
}

int main() {
        clock_t begin = clock();

        FILE *fp;
        char ch;
        char *ss = (char *)malloc(sizeof(char) * 46000);
        char *p;
        char **names = (char **)malloc(sizeof(char) * 46000);
        int sum = 0;
        int i = 0;
        int size = 0;

        if ((fp = fopen("name.txt", "rt")) == NULL)
                exit(1);

        ch = fgetc(fp);

        while (ch != EOF) {
                if (ch == '"') {
                        ch = fgetc(fp);
                        continue;
                }

                ss[i++] = ch;
                ch = fgetc(fp);
        }
        p = strtok(ss, ",");

        while (p != NULL) {
                names[size++] = p;
                p = strtok(NULL, ",");
        }

        sort(names, size);
        for (int j = 0; j < size; j++) {
                int tv = 0;
                for (int l = 0; l < strlen(names[j]); l++) {
                        tv += names[j][l] - 'A' + 1;
                }
                printf("name => %s, index => %d, value => %d\n", names[j], j, tv);
                sum += (j + 1) * tv;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result is %d,  time spend: %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));
        free(names);
        free(ss);

        return 0;
}
