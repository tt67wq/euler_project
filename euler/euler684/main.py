#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import time

# oeis.org A051885


def fibonacci_sequence_mod(n):
    """
    """
    fib = [0, 1]
    for k in range(2, n + 1):
        fib.append(fib[k - 2] + fib[k - 1])

    return fib


def a(n, mod):
    """
    """
    return (pow(10, n // 9, mod) * ((n % 9) + 1) - 1) % mod


def S(n, mod):
    """
    """
    n_mod_9 = n % 9
    print(pow(10, n // 9, mod))
    print((n_mod_9 ** 2 + 3 * n_mod_9 + 12) >> 1)
    return (
        pow(10, n // 9, mod) * ((n_mod_9 ** 2 + 3 * n_mod_9 + 12) >> 1) - 6 - n
    ) % mod


if __name__ == "__main__":
    """
    """
    # T = time.time()
    # F    = 90
    MOD = 1000000007
    # ACC  = 0
    # FIBO = fibonacci_sequence_mod(F)
    # for k in range(2, F + 1):
    #     tmp = S(FIBO[k], MOD)
    #     print(FIBO[k], tmp)
    #     ACC += tmp
    # print (ACC % MOD)
    # print (str(time.time() - T) + " sec.")
    print(S(2880067194370816120, MOD))

