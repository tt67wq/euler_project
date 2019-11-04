/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 500
#define LIST_SIZE 200

unsigned int js_hash(char *str) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;
        int len;

        len = strlen(str);

        for (i = 0; i < len; str++, i++) {
                hash ^= ((hash << 5) + (*str) + (hash >> 2));
        }

        return hash % MAP_SIZE;
}

void add(int *list, int len, int val) {
        int i;
        for (i = 0; i < len; i++) {
                if (list[i] == -1) {
                        list[i] = val;
                        break;
                }
        }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *smallestSufficientTeam(char **req_skills, int req_skillsSize, char ***people, int peopleSize, int *peopleColSize, int *returnSize) {
        int i, j, x, s, n;
        int *dp, *res;
        int **team;
        unsigned int idx;
        int map[MAP_SIZE] = {0};

        if (req_skillsSize == 0) {
                res = (int *)calloc(1, sizeof(int));
                *returnSize = 0;
                return res;
        }

        for (i = 0; i < req_skillsSize; i++) {
                idx = js_hash(req_skills[i]);
                map[idx] = i;
        }

        // init dp
        s = 1 << req_skillsSize;
        dp = (int *)calloc(s, sizeof(int));
        for (i = 0; i < s; i++)
                dp[i] = -1;

        // init team
        team = (int **)calloc(s, sizeof(int *));
        for (i = 0; i < s; i++) {
                team[i] = (int *)calloc(LIST_SIZE, sizeof(int));
                for (j = 0; j < LIST_SIZE; j++)
                        team[i][j] = -1;
        }

        dp[0] = 0;

        for (i = 0; i < peopleSize; i++) {
                n = 0;
                for (j = 0; j < peopleColSize[i]; j++) {
                        idx = js_hash(people[i][j]);
                        n |= (1 << map[idx]);
                }

                for (j = 0; j < s; j++) {
                        if (dp[j] >= 0) {
                                x = n | j;
                                if (dp[x] == -1 || dp[x] > dp[j] + 1) {
                                        dp[x] = dp[j] + 1;
                                        memcpy(team[x], team[j], sizeof(int) * LIST_SIZE);
                                        add(team[x], LIST_SIZE, i);
                                }
                        }
                }
        }

        for (i = 0; i < LIST_SIZE; i++) {
                if (team[s - 1][i] == -1)
                        break;
        }
        *returnSize = i;

        res = (int *)calloc(i, sizeof(int));
        for (j = 0; j < i; j++)
                res[j] = team[s - 1][j];
        return res;
}

int main() {
        int size;
        int col[3] = {1, 1, 2};
        char *req_skills[] = {"java", "nodejs", "reactjs"};
        char ***people = (char ***)calloc(3, sizeof(char **));
        people[0] = (char **)calloc(1, sizeof(char *));
        people[0][0] = "java";

        people[1] = (char **)calloc(1, sizeof(char *));
        people[1][0] = "nodejs";

        people[2] = (char **)calloc(2, sizeof(char *));
        people[2][0] = "nodejs";
        people[2][1] = "reactjs";

        smallestSufficientTeam(req_skills, 3, people, 3, col, &size);

        return 0;
}
