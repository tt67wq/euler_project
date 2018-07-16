/*
 * =====================================================================================
 *
 *       Filename:  knapsack.c
 *
 *    Description:  背包问题
 *
 *        Version:  1.0
 *        Created:  2018-01-03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAXSIZE 7

typedef struct tagObject {
        int weight;
        int price;
        int status; // 0 未选中，1 已选中，2 不可选
} OBJECT;

typedef struct tagKnapsackProblem {
        OBJECT *objs[MAXSIZE];
        int totalC;
} KNAPSACK_PROBLEM;

typedef int (*FunType)(OBJECT *objs[], int);

void GreedyAlgo(KNAPSACK_PROBLEM *problem, FunType spFcun);
int ChooseFunc1(OBJECT *objs[], int c);
int ChooseFunc2(OBJECT *objs[], int c);
int ChooseFunc3(OBJECT *objs[], int c);
void PrintResult(OBJECT *objs[]);

void GreedyAlgo(KNAPSACK_PROBLEM *problem, FunType spFunc) {
        int idx;
        int ntc = 0;

        /* spFunc每次都选出最符合策略的那个物品 */
        while ((idx = spFunc(problem->objs, problem->totalC - ntc)) != -1) {
                /* printf("%d进入候选区\n", idx); */
                if ((ntc + problem->objs[idx]->weight) <= problem->totalC) {
                        printf("挑选出来的物品idx为%d\n", idx);
                        problem->objs[idx]->status = 1;
                        ntc += problem->objs[idx]->weight;
                } else {
                        // 不能选这个物品problem->objs[idx]->status = 2;
                }
        }
        PrintResult(problem->objs);
}

// 取最贵的
int ChooseFunc1(OBJECT *objs[], int c) {
        int index = -1;
        int mp = 0;
        int i;
        for (i = 0; i < MAXSIZE; i++) {
                if ((objs[i]->status == 0) && (objs[i]->price > mp)) {
                        mp = objs[i]->price;
                        index = i;
                }
        }
        return index;
}

// 取最轻的
int ChooseFunc2(OBJECT *objs[], int c) {
        int index = -1;
        int mw = 1000;
        int i;
        for (i = 0; i < MAXSIZE; i++) {
                if ((objs[i]->status == 0) && (objs[i]->weight < mw)) {
                        mw = objs[i]->weight;
                        index = i;
                }
        }
        return index;
}

// 取密度最大的
int ChooseFunc3(OBJECT *objs[], int c) {
        int index = -1;
        float md = 0.0;
        int i;
        for (i = 0; i < MAXSIZE; i++) {
                if ((objs[i]->status == 0) && ((objs[i]->price / (float)(objs[i]->weight)) > md)) {
                        md = objs[i]->price / (float)(objs[i]->weight);
                        index = i;
                }
        }
        return index;
}

void PrintResult(OBJECT *objs[]) {
        int tp = 0;
        for (int i = 0; i < MAXSIZE; i++)
                if (objs[i]->status == 1) {
                        tp += objs[i]->price;
                }
        printf("总价值为%d\n", tp);
}

int main() {
        int w[] = {35, 30, 60, 50, 40, 10, 25};
        int p[] = {10, 40, 30, 50, 35, 40, 30};
        int i;
        KNAPSACK_PROBLEM *problem;
        problem = malloc(sizeof(KNAPSACK_PROBLEM));
        printf("初始化问题数组\n");
        problem->totalC = 150;
        for (i = 0; i < 7; i++) {
                problem->objs[i] = malloc(sizeof(OBJECT));
                problem->objs[i]->weight = w[i];
                problem->objs[i]->price = p[i];
                problem->objs[i]->status = 0;
        }

        GreedyAlgo(problem, ChooseFunc3);
        for (i = 0; i < MAXSIZE; i++)
                free(problem->objs[i]);
        free(problem);
        return 1;
}
