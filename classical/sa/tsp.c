/*
 * =====================================================================================
 *
 *       Filename:  tsp.c
 *
 *    Description:  模拟退火算法解决旅行商问题
 *
 *        Version:  1.0
 *        Created:  2018-09-07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* 旅行商问题，即TSP问题（Traveling Salesman Problem）又译为旅行推销员问题、
   货郎担问题，是数学领域中著名问题之一。
   假设有一个旅行商人要拜访n个城市，他必须选择所要走的路径，路径的限制是每个城市只能拜访一次，
   而且最后要回到原来出发的城市。路径的选择目标是要求得的路径路程为所有路径之中的最小值。 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define T0 50000.0 // 初始温度
#define T_end (1e-8)
#define q 0.98 // 退火系数
#define L 1000 // 每个温度的迭代次数
#define N 31   // 城市数量

int city_list[N]; // 存放解

double city_pos[N][2] = {{1304, 2312}, {3639, 1315}, {4177, 2244}, {3712, 1399}, {3488, 1535},
                         {3326, 1556}, {3238, 1229}, {4196, 1004}, {4312, 790},  {4386, 570},
                         {3007, 1970}, {2562, 1756}, {2788, 1491}, {2381, 1676}, {1332, 695},
                         {3715, 1678}, {3918, 2179}, {4061, 2370}, {3780, 2212}, {3676, 2578},
                         {4029, 2838}, {4263, 2931}, {3429, 1908}, {3507, 2367}, {3394, 2643},
                         {3439, 3201}, {2935, 3240}, {3140, 3550}, {2545, 2357}, {2778, 2826},
                         {2370, 2975}}; // 中国31个城市坐标

// 声明
double distance(double *, double *); // 两个城市距离
double path_len(int *);              // 路径长度
void init();                         // 初始化
void create_new();                   // 产生解析

double distance(double *city1, double *city2) {
        double x1 = *city1;
        double y1 = *(city1 + 1);
        double x2 = *city2;
        double y2 = *(city2 + 1);
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double path_len(int *arr) {
        double path = 0;
        /* int index = *arr; */
        for (int i = 0; i < N - 1; i++) {
                int index1 = *(arr + i);
                int index2 = *(arr + i + 1);
                double dis = distance(city_pos[index1 - 1], city_pos[index2 - 1]);
                path += dis;
        }

        int last_index = *(arr + N - 1);
        int first_index = *arr;

        double last_dis = distance(city_pos[last_index - 1], city_pos[first_index - 1]);
        path += last_dis;
        return path;
}

void init() {
        for (int i = 0; i < N; i++)
                city_list[i] = i + 1;
}

// 用随机交叉两个位置的方式产生解析
void create_new() {
        double r1 = ((double)rand()) / (RAND_MAX + 1.0);
        double r2 = ((double)rand()) / (RAND_MAX + 1.0);

        int pos1 = (int)(N * r1); // 第一个交叉点位置
        int pos2 = (int)(N * r2); // 第二个交叉点位置

        // 交换
        int temp = city_list[pos1];
        city_list[pos1] = city_list[pos2];
        city_list[pos2] = temp;
}

// 主函数
int main() {
        srand((unsigned)time(NULL)); // 随机种子
        time_t start, finish;

        start = clock();

        double T;
        int count = 0; // 降温次数

        T = T0; // 初始温度
        init(); // 初始化一个解

        int city_list_copy[N]; // 保存原始解
        double f1, f2, df; // f1初始目标函数值, f2为新解目标函数值，df为二者差值

        double r;

        while (T > T_end) { // 当温度低于结束温度的时候，结束退火
                for (int i = 0; i < L; i++) {
                        memcpy(city_list_copy, city_list, N * sizeof(int)); // 复制数组
                        create_new();                                       // 产生新解
                        f1 = path_len(city_list_copy);
                        f2 = path_len(city_list);
                        df = f2 - f1;

                        /* Metropolis准则 */
                        if (df >= 0) {
                                r = ((double)rand()) / (RAND_MAX);
                                if (exp(-df / T) <= r)
                                        memcpy(city_list, city_list_copy, N * sizeof(int));
                        }
                }
                T *= q; // 降温
                count++;
        }
        finish = clock();

        double duration = ((double)(finish - start)) / CLOCKS_PER_SEC; // 计算时间

        printf("采用模拟退火算法，初始温度T0=%.2f, "
               "降温系数q=%.2f，每个温度迭代%d次，共降温%d次，得到TSP最优路径为：\n",
               T0, q, L, count);
        for (int i = 0; i < N - 1; i++)
                printf("%d -->", city_list[i]);
        printf("%d\n", city_list[N - 1]);

        double len = path_len(city_list);

        printf("最优路径长度: %lf\n", len);
        printf("程序运行耗时: %lf秒\n", duration);
        return 0;
}
