#ifndef __BIGINT__
#define __BIGINT__

#include "kvec.h"
#include <stdio.h>
#include <string.h>

typedef kvec_t(int) bigint;

bigint new_bigint(char *);
void print_bigint(bigint);
bigint add(bigint, bigint);
bigint multiply(bigint, bigint);

#endif
