/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-02
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0
#define VISITING 1
#define VISITED 2

int **edges;
int *edgesColSize;
int *visited;
int *result;
int resultSize;
bool valid;

void dfs(int u) {
        visited[u] = VISITING;
        for (int i = 0; i < edgesColSize[u]; ++i) {
                if (visited[edges[u][i]] == UNVISITED) {
                        dfs(edges[u][i]);
                        if (!valid)
                                return;
                } else if (visited[edges[u][i]] == VISITING) {
                        valid = false;
                        return;
                } else {
                        ;
                }
        }
        visited[u] = VISITED;
        result[resultSize++] = u;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize, int *returnSize) {
        valid = true;
        edges = (int **)calloc(numCourses, sizeof(int *));
        for (int i = 0; i < numCourses; i++) {
                edges[i] = (int *)malloc(0);
        }

        edgesColSize = (int *)calloc(numCourses, sizeof(int));
        visited = (int *)calloc(numCourses, sizeof(int));

        for (int i = 0; i < prerequisitesSize; ++i) {
                int a = prerequisites[i][1], b = prerequisites[i][0];
                edgesColSize[a]++;
                edges[a] = (int *)realloc(edges[a], sizeof(int) * edgesColSize[a]);
                edges[a][edgesColSize[a] - 1] = b;
        }
        result = (int *)calloc(numCourses, sizeof(int));
        resultSize = 0;

        for (int i = 0; i < numCourses && valid; i++) {
                if (!visited[i]) {
                        dfs(i);
                }
        }

        for (int i = 0; i < numCourses; i++) {
                free(edges[i]);
        }

        free(edges);
        free(edgesColSize);
        free(visited);

        if (!valid) {
                *returnSize = 0;
        } else {
                // reverse
                for (int i = 0; i < numCourses / 2; i++) {
                        int t = result[i];
                        result[i] = result[numCourses - i - 1], result[numCourses - i - 1] = t;
                }
                *returnSize = resultSize;
        }
        return result;
}

int main() {
        int numCourses = 4;
        int pr0[] = {1, 0};
        int pr1[] = {2, 0};
        int pr2[] = {3, 1};
        int pr3[] = {3, 2};

        int *prerequisites[] = {pr0, pr1, pr2, pr3};

        int prerequisitesSize = 4;
        int prerequisitesColSize[] = {2, 2, 2, 2};
        int returnSize = 0;

        int *result = findOrder(numCourses, prerequisites, prerequisitesSize, prerequisitesColSize,
                                &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d\t", result[i]);
        }
        printf("\n");

        return 0;
}