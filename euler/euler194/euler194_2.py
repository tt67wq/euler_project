#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


def pieceA_pol(n):
    return (38 * n
            - 115 * n**2
            + 146 * n**3
            - 103 * n**4
            + 43 * n**5
            - 10 * n**6
            + 1 * n**7)


def pieceB_pol(n):
    return (+24 * n
            - 76 * n**2
            + 102 * n**3
            - 77 * n**4
            + 35 * n**5
            - 9 * n**6
            + 1 * n**7)


def product(xs):
    output = 1
    for x in xs:
        output *= x
    return output


def binomial(n, m):
    return product(range(n-m+1, n+1)) // product(range(1, m+1))


def main():
    col = 1984
    na = 25
    nb = 75
    pieA = pieceA_pol(col)
    pieA_red = pieA // (col * (col - 1))
    pieB = pieceB_pol(col)
    pieB_red = pieB // (col * (col - 1))
    sol = (pieA * binomial(na+nb-1, nb) * pieA_red**(na-1) * pieB_red**nb +
           pieB * binomial(na+nb-1, na) * pieA_red**na * pieB_red**(nb-1))
    print(sol % (10**8))


if __name__ == '__main__':
    main()
