/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-07
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

#define DEBUG
#define UNVISITED 0
#define VISITING 1
#define VISITED 2

int **edges;
int *edgesColSize;
int *visited;
bool valid;

void dfs(int u) {
        visited[u] = VISITING;
        for (int i = 0; i < edgesColSize[u]; i++) {
                if (visited[edges[u][i]] == UNVISITED) {
                        dfs(edges[u][i]);
                        if (!valid) {
                                return;
                        }
                } else if (visited[edges[u][i]] == VISITING) {
                        valid = false;
                        return;
                } else {
                        // VISITED
                        ;
                }
        }
        visited[u] = VISITED;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize,
               int *prerequisitesColSize) {
        valid = true;
        edges = (int **)calloc(numCourses, sizeof(int *));
        for (int i = 0; i < numCourses; i++) {
                edges[i] = (int *)calloc(100, sizeof(int));
        }
        edgesColSize = (int *)calloc(numCourses, sizeof(int));
        visited = (int *)calloc(numCourses, sizeof(int));
        for (int i = 0; i < numCourses; i++) {
                visited[i] = UNVISITED;
        }

        for (int i = 0; i < prerequisitesSize; i++) {
                int after = prerequisites[i][1], before = prerequisites[i][0];
                edges[after][edgesColSize[after]] = before;
                edgesColSize[after]++;
        }
        for (int i = 0; i < numCourses && valid; i++) {
                if (visited[i] == UNVISITED) {
                        dfs(i);
                }
        }
        for(int i=0;i<numCourses;i++){
            free(edges[i]);
        }
        free(edges);
        free(edgesColSize);
        free(visited);

        return valid;
}

int main() { return 0; }