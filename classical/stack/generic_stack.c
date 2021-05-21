/*
 * =====================================================================================
 *
 *       Filename:  generic_stack.c
 *
 *    Description: 泛型栈
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
                printf("don't need be free\n");
        else {
                printf("free lefted elements\n");
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

int main() {
        typedef struct student {
                char name[10];
                int age;
        } student;

        student stu[5] = {{"Jonh", 10}, {"Jim", 11}, {"Allen", 12}, {"Ewa", 13}, {"Walle", 14}};
        stack s;
        stackNew(&s, sizeof(student *), strfree);
        for (int i = 0; i < 5; ++i) {
                student *pstu = (student *)malloc(sizeof(student));
                memcpy(pstu, &stu[i], sizeof(student));
                stackPush(&s, &pstu);
        }
        for (int i = 0; i < 3; ++i) {
                student *ps;
                stackPop(&s, &ps);
                printf("pop student %s.\n", ps->name);
                free(ps);
        }
        stackDispose(&s);
        return 0;
}
