/*
* =====================================================================================
*
*       Filename:  main.c
*
*    Description:  
*
*        Version:  1.0
*        Created:  2020-06-28
*       Revision:  none
*       Compiler:  clang
*
*         Author:  
*
* =====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

// 对正整数n，欧拉函数是小于或等于n的正整数中与n互质的数的数目（因此φ(1)=1）。
// 此函数以其首名研究者欧拉命名(Euler's totient function)，
// 它又称为Euler's totient function、φ函数、欧拉商数等。 例如φ(8)=4，因为1,3,5,7均和8互质。 

// φ(p) = p - 1 if p is prime
// φ(p^k) = p^(k-1) x (p - 1) if p is prime
// φ(xy) = φ(x) x φ(y) if x, y are coprime
int eular(int n) {
        int ret = 1, i;
        for (i = 2; i * i <= n; i++) {
                if (n % i == 0) {
                        n /= i, ret *= i - 1;
                        while (n % i == 0)
                                n /= i, ret *= i;
                }
        }
        if (n > 1)
                ret *= n - 1;
        return ret;
}


int main() { return 0; }