/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        void *elemType;
        int elemSize;
        int size;
        int capacity;
        void (*pfree)(void *);
} stack, *pstack;

void stackNew(pstack s, int elemSize, void (*pfree)(void *));
void stackDispose(pstack s);
void stackPush(pstack s, void *valAddr);
void stackPop(pstack s, void *valAddr);
static void sizeGrow(pstack s);

void stackNew(pstack s, int elemSize, void (*pfree)(void *)) {
        s->capacity = 4;
        s->elemSize = elemSize;
        s->size = 0;
        s->pfree = pfree;
        s->elemType = malloc(s->capacity * elemSize);
        assert(s->elemType);
}

void stackDispose(pstack s) {
        if (s->pfree == NULL || s->size == 0)
                ;
        else {
                for (int i = 0; i < s->size; ++i) {
                        char *del = (char *)s->elemType + i * s->elemSize;
                        s->pfree(del);
                }
        }
        free(s->elemType);
}

void stackPush(pstack s, void *valAddr) {
        if (s->size == s->capacity)
                sizeGrow(s);
        void *target = s->elemType + s->size * s->elemSize;
        memcpy(target, valAddr, s->elemSize);
        ++s->size;
}

static void sizeGrow(pstack s) {
        s->capacity *= 2;
        s->elemType = realloc(s->elemType, s->capacity * s->elemSize);
        assert(s->elemType);
}

void stackPop(pstack s, void *valAddr) {
        assert(s->size);
        --s->size;
        void *source = s->elemType + s->size * s->elemSize;
        memcpy(valAddr, source, s->elemSize);
}

void strfree(void *pstr) {
        char *del = *(char **)pstr;
        free(del);
}

void reverse_string(char *str) {
        /* skip null */
        if (str == 0) {
                return;
        }

        /* skip empty string */
        if (*str == 0) {
                return;
        }

        /* get range */
        char *start = str;
        char *end = start + strlen(str) - 1; /* -1 for \0 */
        char temp;

        /* reverse */
        while (end > start) {
                /* swap */
                temp = *start;
                *start = *end;
                *end = temp;

                /* move */
                ++start;
                --end;
        }
}

int process(char *s) {
        int i, l, ans, sign;
        unsigned int acc;

        l = strlen(s);
        acc = 0;
        sign = 1;
        ans = 0;

        for (i = 0; i < l; i++) {
                if (s[i] == ' ')
                        continue;

                if (s[i] == '+') {
                        if (sign == 1)
                                ans += acc;
                        else
                                ans -= acc;
                        sign = 1;
                        acc = 0;
                        continue;
                }

                if (s[i] == '-') {
                        if (sign == 1)
                                ans += acc;
                        else
                                ans -= acc;

                        acc = 0;
                        sign = -1;
                        continue;
                }

                acc = acc * 10 + s[i] - '0';
        }
        if (sign == 1)
                ans += acc;
        else
                ans -= acc;

        return ans;
}

int calculate(char *s) {
        stack *st;
        int i, j, l, x;
        char buffer[16384];
        char nums[10];

        st = (stack *)calloc(1, sizeof(stack));
        stackNew(st, sizeof(char *), strfree);
        l = strlen(s);
        /* tmp = (char *)calloc(1, sizeof(char)); */

        for (i = 0; i < l; i++) {
                if (s[i] == ' ')
                        continue;
                if (s[i] == ')') {
                        bzero(buffer, sizeof(char) * 16384);
                        bzero(nums, sizeof(char) * 10);
                        j = 0;
                        while (1) {
                                char *tmp;
                                stackPop(st, &tmp);
                                if (*tmp == '(') {
                                        free(tmp);
                                        break;
                                }
                                buffer[j++] = *tmp;
                                free(tmp);
                        }
                        reverse_string(buffer);
                        x = process(buffer);
                        /* printf("%s = %d\n", buffer, x); */
                        j = 0;
                        if (x > 0) {
                                while (x > 0) {
                                        nums[j++] = x % 10 + '0';
                                        x /= 10;
                                }
                        } else {
                                x *= -1;
                                while (x > 0) {
                                        nums[j++] = x % 10 + '0';
                                        x /= 10;
                                }
                                char *tmp;
                                if (st->size == 0) {
                                        tmp = (char *)calloc(1, sizeof(char));
                                        *tmp = '+';
                                } else {
                                        stackPop(st, &tmp);
                                }

                                if (*tmp == '-') {
                                        nums[j++] = '+';
                                } else {
                                        nums[j++] = '-';
                                }
                                free(tmp);
                        }

                        j--;
                        for (; j > -1; j--) {
                                char *tmp;
                                tmp = (char *)calloc(1, sizeof(char));
                                memcpy(tmp, &nums[j], sizeof(char));
                                stackPush(st, &tmp);
                        }
                        continue;
                }
                char *tmp;
                tmp = (char *)calloc(1, sizeof(char));
                memcpy(tmp, &s[i], sizeof(char));
                stackPush(st, &tmp);
        }

        bzero(buffer, sizeof(char) * 16384);
        j = 0;
        while (st->size > 0) {
                char *tmp;
                stackPop(st, &tmp);
                buffer[j++] = *tmp;
                free(tmp);
        }
        stackDispose(st);
        free(st);

        reverse_string(buffer);
        /* printf("%s\n", buffer); */
        return process(buffer);
}

int main() {
        char s[] = "2-(1-2)";
        printf("%d\n", calculate(s));

        return 0;
}
