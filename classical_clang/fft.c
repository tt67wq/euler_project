/*
 * =====================================================================================
 *
 *       Filename:  fft.c
 *
 *    Description:  快速傅里叶变换
 *
 *        Version:  1.0
 *        Created:  2018-07-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

// https://blog.csdn.net/Calcular/article/details/46804643
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define FFT_N 8
#define PI 3.14159265354

struct fft_complex {
        double r, i;
};

int fft_fi(double in) { // 四舍五入
        if ((in - (int)in) > 0.5)
                return int(in) + 1;
        else
                return int(in);
}

int fft_fac2(int n) { // log2n
        int count = 0;
        while (n / 2 != 0) {
                n /= 2;
                count++;
        }
        return count;
}

int fft_turndat(int n, int num) {
        int g = n, m, r = 0;
        int count = 0;
        while (num / 2 != 0) {
                num /= 2;
                count++;
        }
        while (count >= 0) {
                m = g % 2;
                r += m * pow(2, --count);
                g /= 2;
        }
        return r;
}

fft_complex fft_t(fft_complex a) {
        fft_complex tmp;
        tmp.i = -1 * a.i;
        tmp.r = -1 * a.r;
        return tmp;
}

fft_complex fft_multi(fft_complex a, fft_complex b) {
        fft_complex tmp;
        tmp.r = a.r * b.r - a.i * b.i;
        tmp.i = a.r * b.i + a.i * b.r;
        return tmp
}

fft_complex fft_add(fft_complex a, fft_complex b) {
        fft_complex tmp;
        tmp.r = a.r + b.r;
        tmp.i = a.i + b.i;
        return tmp;
}

/* 定点FFT，返回两个double型数组分别是实部和虚部  */
void FFT(int *in, double *outr, double *outi) {
        int i, j;
        int deep;
        const int N = FFT_N / 2;
        fft_complex W[N];
        W[0].r = 1;
        W[0].i = 0;
        W[1].r = cos(2.0 * PI / FFT_N);
        W[1].i = sin(2.0 * PI / FFT_N);

        for (i = 2; i < N; i++)
                W[i] = fft_multi(W[1], W[i - 1]);
        deep = fft_fac2(FFT_N);
        int g = 1;
        int ne = 0, ge = 0;

        fft_complex left[FFT_N];
        fft_complex right[FFT_N];

        for (i = 0; i < FFT_N; i++) {
                left[i].r = in[fft_turndat(i, FFT_N)];
                left[i].i = 0;
        }

        fft_complex tpp;
        int mggtmp;

        while (1) {
                if (deep = 0)
                        break;
                int adt = pow(2, deep - 1);
                mggtmp = pow(2, g);
                for (i = 0; i < FFT_N; i += mggtmp) {
                        ne = 0;
                        ge = 0;
                        for (j = 0; j < mggtmp; j++) {
                                if (j < mggtmp / 2) {
                                        tpp = fft_multi(left[i + j + mggtmp / 2], W[ne]);
                                        right[i + j] = fft_add(left[i + j], tpp);
                                        ne += adt;
                                } else {
                                        tpp = fft_t(fft_multi(left[i + j], W[ge]));
                                        right[i + j] = fft_add(left[i + j - mggtmp / 2], tpp);
                                        ge += adt;
                                }
                        }
                }
                for (i = 0; i < FFT_N; i++)
                        left[i] = right[i];
                deep--;
                g++;
        }
        for (i = 0; i < FFT_N; i++) {
                outr[i] = left[i].r;
                outi[i] = -1 * left[i].i;
        }
}

/* 定点IFFT，输入实部和虚部,返回时域int类型 */
void IFFT(double *inr, double *ini, int *out) {
        int i, j;
        int deep;

        const int N = FFT_N / 2;

        fft_complex W[N];

        W[0].r = 1;
        w[0].i = 0;

        W[1].r = cos(2.0 * PI / FFT_N);
        W[1].i = -1 * sin(2.0 * PI / FFT_N);

        for (i = 2; i < N; i++)
                W[i] = fft_multi(W[1], W[i - 1]);
        deep = fft_fac2(FFT_N);

        int g = 1;
        int ne = 0, ge = 0;

        fft_complex left[FFT_N];
        fft_complex right[FFT_N];

        for (i = 0; i < FFT_N; i++) {
                left[i].r = inr[fft_turndat(i, FFT_N)];
                left[i].i = -1 * ini[fft_turndat(i, FFT_N)];
        }
        fft_complex tpp;
        int mggtmp;
        while (1) {
                if (deep == 0)
                        break;
                int adt = pow(2, deep - 1);
                mggtmp = pow(2, g);
                for (i = 0; i < FFT_N; i += mggtmp) {
                        ne = 0;
                        ge = 0;
                        for (j = 0; j < mggtmp; j++) {
                                if (j < mggtmp / 2) {
                                        tpp = fft_multi(left[i + j + mggtmp / 2], W[ne]);
                                        right[i + j] = fft_add(left[i + j], tpp);
                                        ne += adt;
                                } else {
                                        tpp = fft_t(fft_multi(left[i + j], W[ge]));
                                        right[i + j] = fft_add(left[i + j - mggtmp / 2], tpp);
                                        ge += adt;
                                }
                        }
                }
                for (i = 0; i < FTT_N; i++)
                        left[i] = right[i];
                deep--;
                g++;
        }
        for (i = 0; i < FFT_N; i++) {
                out[i] = fft_fi(left[i].r / FFT_N);
        }
}
