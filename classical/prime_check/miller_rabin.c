/*
 * =====================================================================================
 *
 *       Filename:  miller_rabin.c
 *
 *    Description:  米勒罗宾素数判断方法
 *
 *        Version:  1.0
 *        Created:  2018-08-13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 计算 m^n % k
uint64_t pow_mod(uint64_t m, uint64_t n, uint64_t k) {
        if (n == 1)
                return m % k;
        if (n == 2)
                return (m * m) % k;

        if (m % k == 0)
                return 0;

        uint64_t b = pow_mod(m, 2, k);
        if (n % 2 == 0) {
                return pow_mod(b, n >> 1, k);
        } else {
                return (m * pow_mod(b, (n - 1) >> 1, k)) % k;
        }
}

uint64_t random2(uint64_t high) {
        if (high == 2)
                return 2;
        return rand() % (high - 2) + 2;
}

// 二次探测
int double_check(uint64_t tu, uint64_t n, uint64_t x) {
        /* printf("tu => %d, n => %d, x =>%d\n", tu, n, x); */
        if (tu >= n)
                return x;
        uint64_t y = pow_mod(x, 2, n);

        if (y == 1 && x != 1 && x != n - 1)
                return 0;
        else
                return double_check(tu << 1, n, y);
}

uint64_t get_u(uint64_t u) {
        while (1) {
                if (u % 2 == 1)
                        break;
                u = u >> 1;
        }
        return u;
}

// 费马检测
int fermat_check(uint64_t n, uint64_t u, int s) {
        if (s == 0)
                return 1;
        uint64_t a = random2(n - 1);
        uint64_t x = pow_mod(a, u, n);
        int flag = double_check(u, n, x);

        if (flag > 0) {
                if (flag == 1)
                        return fermat_check(n, u, s - 1);
                else
                        return 0;
        } else
                return 0;
}

int probablyPrime(uint64_t n, int times) {
        if (n == 1)
                return 0;
        if (n == 2)
                return 1;
        if (n % 2 == 0)
                return 0;
        return fermat_check(n, get_u(n - 1), times);
}

// 用于比较效果用的
int isPrime(uint64_t n) {
        if (n == 1)
                return 0;
        for (int i = 2; i <= sqrt(n); i++) {
                if (n % i == 0)
                        return 0;
        }
        return 1;
}

int main() {
        uint64_t index = 1;
        while (1) {
                int res1 = probablyPrime(index, 3);
                int res2 = isPrime(index);

                printf("%llu => <%d, %d>\n", index, res1, res2);
                if (res1 != res2) {
                        printf("%llu => <%d, %d>\n", index, res1, res2);
                        break;
                }

                index++;
        }
        return 0;
}
