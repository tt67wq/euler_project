/*
 * =====================================================================================
 *
 *       Filename:  euler_problem12.c
 *
 *    Description:  欧拉计划12题
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

#include "hashmap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("fac")
#define KEY_COUNT (1024 * 1024)

typedef struct data_struct_s {
        char key_string[KEY_MAX_LENGTH];
        int number;
} data_struct_t;

// 质因数分解
void factorize(int num, int *facs, int *len) {
        int i, j = 0;
        for (i = 2; i <= sqrt(num); i++) {
                if (num % i == 0) {
                        num /= i;
                        facs[j++] = i--;
                }
        }
        facs[j] = num;
        *len = j;
}

int main() {
        int num;
        printf("请输入想分解的数字: \n");
        scanf("%d", &num);
        int *facs = (int *)malloc(500 * sizeof(int));
        int len;
        int error;
        factorize(num, facs, &len);
        int nums[len];
        map_t hmap = hashmap_new();
        for (int i = 0; i <= len; i++) {
                char key[KEY_MAX_LENGTH];
                snprintf(key, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, facs[i]);
                data_struct_t *value;

                error = hashmap_get(hmap, key, (void **)(&value));
                if (error == MAP_MISSING) {
                        value = malloc(sizeof(data_struct_t));
                        snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, facs[i]);
                        value->number = 1;
                        hashmap_put(hmap, value->key_string, value);
                        nums[i] = facs[i];
                } else {
                        value->number += 1;
                        hashmap_put(hmap, value->key_string, value);
                }
        }

        for (int i = 0; i <= len; i++) {
                char key[KEY_MAX_LENGTH];
                data_struct_t *value;
                snprintf(key, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, nums[i]);
                error = hashmap_get(hmap, key, (void **)(&value));
                if (error == MAP_OK)
                        printf("%d => %d\n", nums[i], value->number);
        }

        return 0;
}
