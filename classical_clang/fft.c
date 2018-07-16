/*
 * =====================================================================================
 *
 *       Filename:  fft.c
 *
 *    Description:  傅里叶变换
 *
 *        Version:  1.0
 *        Created:  2018-07-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000
typedef struct {
        double real;
        double img;
} complex;
void fft();  /*快速傅里叶变换*/
void ifft(); /*快速傅里叶逆变换*/
void initW();
void change();
void add(complex, complex, complex *);  /*复数加法*/
void mul(complex, complex, complex *);  /*复数乘法*/
void sub(complex, complex, complex *);  /*复数减法*/
void divi(complex, complex, complex *); /*复数除法*/
void output();                          /*输出结果*/

complex x[N], *W; /*输出序列的值*/
int size_x = 0;   /*输入序列的长度，只限2的N次方*/
double PI;

int main() {
        int i, method;

        system("cls");
        PI = atan(1) * 4;
        printf("Please input the size of x:\n");
        /*输入序列的长度*/
        scanf("%d", &size_x);
        printf("Please input the data in x[N]:(such as:5 6)\n");
        /*输入序列对应的值*/
        for (i = 0; i < size_x; i++)
                scanf("%lf %lf", &x[i].real, &x[i].img);
        initW();
        /*选择FFT或逆FFT运算*/
        printf("Use FFT(0) or IFFT(1)?\n");
        scanf("%d", &method);
        if (method == 0)
                fft();
        else
                ifft();
        output();
        return 0;
}

/*进行基-2 FFT运算*/
void fft() {
        int i = 0, j = 0, k = 0, l = 0;
        complex up, down, product;
        change();
        for (i = 0; i < log(size_x) / log(2); i++) {
                l = 1 << i;
                for (j = 0; j < size_x; j += 2 * l) {
                        for (k = 0; k < l; k++) {
                                mul(x[j + k + l], W[size_x * k / 2 / l], &product); // 旋转算子
                                add(x[j + k], product, &up);                        // up
                                sub(x[j + k], product, &down);                      // down
                                x[j + k] = up;
                                x[j + k + l] = down;
                        }
                }
        }
}

/* FFT逆运算 */
void ifft() {
        int i = 0, j = 0, k = 0, l = size_x;
        complex up, down;
        for (i = 0; i < (int)(log(size_x) / log(2)); i++) /*蝶形运算*/
        {
                l /= 2;
                for (j = 0; j < size_x; j += 2 * l) {
                        for (k = 0; k < l; k++) {
                                add(x[j + k], x[j + k + l], &up);
                                up.real /= 2;
                                up.img /= 2;
                                sub(x[j + k], x[j + k + l], &down);
                                down.real /= 2;
                                down.img /= 2;
                                divi(down, W[size_x * k / 2 / l], &down);
                                x[j + k] = up;
                                x[j + k + l] = down;
                        }
                }
        }
        change();
}

void initW() {
        int i;
        W = (complex *)malloc(sizeof(complex) * size_x);
        for (i = 0; i < size_x; i++) {
                W[i].real = cos(2 * PI / size_x * i);
                W[i].img = -1 * sin(2 * PI / size_x * i);
        }
}

void change() {
        complex temp;
        unsigned short i = 0, j = 0, k = 0;
        double t;
        for (i = 0; i < size_x; i++) {
                k = i;
                j = 0;
                t = (log(size_x) / log(2));
                while ((t--) > 0) {
                        j = j << 1;
                        j |= (k & 1);
                        k = k >> 1;
                }
                if (j > i) {
                        temp = x[i];
                        x[i] = x[j];
                        x[j] = temp;
                }
        }
}

void output() /*输出结果*/
{
        int i;
        printf("The result are as follows\n");
        for (i = 0; i < size_x; i++) {
                printf("%.4f", x[i].real);
                if (x[i].img >= 0.0001)
                        printf("+%.4fj\n", x[i].img);
                else if (fabs(x[i].img) < 0.0001)
                        printf("\n");
                else
                        printf("%.4fj\n", x[i].img);
        }
}
void add(complex a, complex b, complex *c) {
        c->real = a.real + b.real;
        c->img = a.img + b.img;
}

void mul(complex a, complex b, complex *c) {
        c->real = a.real * b.real - a.img * b.img;
        c->img = a.real * b.img + a.img * b.real;
}
void sub(complex a, complex b, complex *c) {
        c->real = a.real - b.real;
        c->img = a.img - b.img;
}
void divi(complex a, complex b, complex *c) {
        c->real = (a.real * b.real + a.img * b.img) / (b.real * b.real + b.img * b.img);
        c->img = (a.img * b.real - a.real * b.img) / (b.real * b.real + b.img * b.img);
}
