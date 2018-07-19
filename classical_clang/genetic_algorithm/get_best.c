/*
 * =====================================================================================
 *
 *       Filename:  get_best.c
 *
 *    Description:  遗传算法求f = -5*sin(x1)*sin(x2)*sin(x3)*sin(x4)*sin(x5) - sin(5*x1)*sin(5*x2)*sin(5*x3)*sin(5*x4)*sin(5*x5) + 8的最小值
 *
 *        Version:  1.0
 *        Created:  2018-07-19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

/* https://www.cnblogs.com/lyrichu/p/6152897.html */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.1415926               // 圆周率
#define sizepop 50                 // 种群大小
#define maxgen 500                 // 进化代数
#define pcross 0.6                 // 交叉概率
#define pmutation 0.1              // 变异概率
#define lenchrom 5                 // 染色体长度
#define bound_down 0               // 变量下届
#define bound_up (0.9 * 3.1415926) // 上届

double chrom[sizepop][lenchrom]; // 种群数组
double fitness[sizepop];         // 个体适应度
double fitness_prob[sizepop];    // 个体被选中的概率
double bestfitness[maxgen];      // 每一代的最优值
double gbest_pos[lenchrom];      // 最优值的位置
double gbest;                    // 最优值
int gbest_index;                 // 最优值下标

// 目标函数
double fit_func(double *arr) {
        double x1 = *arr;
        double x2 = *(arr + 1);
        double x3 = *(arr + 2);
        double x4 = *(arr + 3);
        double x5 = *(arr + 4);
        return -5 * sin(x1) * sin(x2) * sin(x3) * sin(x4) * sin(x5) - sin(5 * x1) * sin(5 * x2) * sin(5 * x3) * sin(5 * x4) * sin(5 * x5) + 8;
}

// 求和
double sum(double *fitness) {
        double sum_fit = 0;
        for (int i = 0; i < sizepop; i++) {
                sum_fit += *(fitness + i);
        }
        return sum_fit;
}

// 求最小值
double *min(double *fitness) {
        double min_fit = *fitness;
        double min_index = 0;
        static double arr[2];
        for (int i = 1; i < sizepop; i++) {
                if (*(fitness + i) < min_fit) {
                        min_fit = *(fitness + i);
                        minx_index = i;
                }
        }
        arr[0] = min_index;
        arr[1] = min_fit;
        return arr;
}

void init_chrom() {
        for (int i = 0; i < sizepop; i++) {
                for (int j = 0; j < lenchrom; j++)
                        chrom[i][j] = bound_up * ((double)rand() / RAND_MAX);
                fitness[i] = fit_func(chrom[i]);
        }
}

// 自然选择
void select(double chrom[sizepop][lenchrom]) {
        int index[sizepop];
        for (int i = 0; i < sizepop; i++) {
                double *arr = chrom[i];
                fitness[i] = 1 / (fit_func(arr));
        }
        double sum_fitness = 0;
        for (int i = 0; i < sizepop; i++)
                sum_fitness += fitness[i];

        for (int i = 0; i < sizepop; i++)
                fitness_prob[i] = fitness[i] / sum_fitness; // 适应程度越高，被选中的概率越大

        for (int i = 0; i < sizepop; i++)
                fitness[i] = 1 / fitness[i];

        for (int i = 0; i < sizepop; i++) { // 俄罗斯轮盘赌算法
                double pick = ((double)rand()) / RAND_MAX;
                while (pick < 0.0001)
                        pick = ((double)rand()) / RAND_MAX;
                for (int j = 0; j < sizepop; j++) {
                        pick = pick - fitness_prob[j];
                        if (pick < 0) {
                                index[i] = j;
                                break;
                        }
                }
        }

        for (int i = 0; i < sizepop; i++) {
                for (int j = 0; j < lenchrom; j++)
                        chrom[i][j] = chrom[index[i]][j];
                fitness[i] = fitness[index[j]];
        }
}
