/*
 * =====================================================================================
 *
 *       Filename:  guass_eqution.c
 *
 *    Description:  高斯消元法
 *
 *        Version:  1.0
 *        Created:  2018-07-04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

// compile: gcc guass_eqution.c -o guass

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAX 10

double A[MAX][MAX]; // 系数
double b[MAX];      // 常数项
double X[MAX];      // 迭代向量
int NUM;            // A的阶数
int size;           // 最大迭代次数

int main(void) {
        int i, j, k; // 计数器
        float Aik;   // 正消过程中用到的变量名
        float S;     // 回消过程中用到的变量名

        // 输入矩阵系数
        printf("请输入系数矩阵A的阶数:");
        scanf("%d", &NUM);

        size = NUM;
        printf("您将组件一个%d阶矩阵\n", size);
        for (i = 0; i < size; i++) {
                printf("请输入A的第%d行元素，各元素之间以空格间隔:\n", i + 1);
                for (j = 0; j < size; j++)
                        scanf("%lf", &A[i][j]);
        }

        printf("输入右端项，各个元素之间以空格间隔: \n");
        for (i = 0; i < size; i++) {
                scanf("%lf", &b[i]);
        }

        // 输入完成
        printf("您输入的维度是%d的矩阵为A[][]:\n\n", NUM);
        for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++)
                        printf("%lf\t", A[i][j]);
                printf("%lf", b[i]);
                printf("\n\v");
        }

        // 高斯消元法主要逻辑

        // 正向消元
        for (k = 0; k < size - 1; k++) {
                // 第k行
                if (!A[k][k])
                        return -1;

                for (i = k + 1; i < size; i++) {
                        Aik = A[i][k] / A[k][k]; // 第i行与第k行 第k个元素比值
                        for (j = k; j < size; j++)
                                A[i][j] -= Aik * A[k][j]; // 消除掉第k个元素
                        b[i] -= Aik * b[k];
                }
        }

        // 打印正向消元后的结果
        printf("正向消元后的结果: \n");
        for (i = 0; i < size; i++) {
                for (j = 0; j < size; j++)
                        printf("%lf\t", A[i][j]);
                printf("%lf", b[i]);
                printf("\n\n");
        }

        // 逆向消元
        X[size - 1] = b[size - 1] / A[size - 1][size - 1];
        for (k = size - 2; k >= 0; k--) {
                S = b[k]; // 第k行的常数项
                for (j = k + 1; j < size; j++)
                        S -= A[k][j] * X[j];
                X[k] = S / A[k][k];
        } // 回代

        // 此处打印出向量
        printf("The solution is x[]=\n\n");
        for (i = 0; i < size; i++)
                printf("\t%f\t\n\n", X[i]);
        return 0;
}
