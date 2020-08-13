/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MAX_LENGTH 21

typedef struct browserHistory {
        char *url;
        struct browserHistory *next;
        struct browserHistory *prev;
} BrowserHistory;

BrowserHistory *browserHistoryCreate(char *homepage) {
        // strlen(homepage);
        BrowserHistory *obj = (BrowserHistory *)malloc(sizeof(BrowserHistory));
        obj->url = (char *)malloc(MAX_LENGTH * sizeof(char));
        obj->next = NULL;
        obj->prev = NULL;
        strncpy(obj->url, homepage, strlen(homepage) + 1);
        return obj;
}

void browserHistoryVisit(BrowserHistory *obj, char *url) {
        printf("visit %s\n", url);
        BrowserHistory *newObj = (BrowserHistory *)malloc(sizeof(BrowserHistory));
        newObj->url = (char *)malloc(MAX_LENGTH * sizeof(char));
        strncpy(newObj->url, url, strlen(url) + 1);
        newObj->next = NULL;
        newObj->prev = obj;

        // clear tails
        BrowserHistory *p0 = obj->next;
        BrowserHistory *p1 = p0;
        while (p0) {
                p1 = p0;
                p0 = p0->next;
                free(p1->url);
                free(p1);
        }
        obj->next = newObj;
        obj = obj->next;
}

char *browserHistoryBack(BrowserHistory *obj, int steps) {
        int n = steps;
        BrowserHistory *ptr0 = obj->prev;
        BrowserHistory *ptr1 = obj;
        while (n) {
                if (ptr0 == NULL) {
                        break;
                }
                ptr1 = ptr0;
                ptr0 = ptr0->prev;
                n--;
        }
        return ptr1->url;
}

char *browserHistoryForward(BrowserHistory *obj, int steps) {
        int n = steps;
        BrowserHistory *ptr0 = obj->next;
        BrowserHistory *ptr1 = obj;

        while (n) {
                if (ptr0 == NULL) {
                        break;
                }
                ptr1 = ptr0;
                ptr0 = ptr0->next;
                n--;
        }
        return ptr1->url;
}

void browserHistoryFree(BrowserHistory *obj) {
        // back to head
        BrowserHistory *ptr0 = obj->prev;
        BrowserHistory *ptr1 = obj;
        while (ptr0) {
                ptr1 = ptr0;
                ptr0 = ptr0->prev;
        }

        // clear from head
        ptr0 = ptr1->next;
        free(ptr1->url);
        free(ptr1);
        while (ptr0) {
                ptr1 = ptr0;
                ptr0 = ptr0->next;

                free(ptr1->url);
                free(ptr1);
        }
}

int main() {

        BrowserHistory *obj = browserHistoryCreate("root");

        browserHistoryVisit(obj, "b");
        browserHistoryVisit(obj, "c");
        browserHistoryVisit(obj, "d");
        printf("%s\n", browserHistoryBack(obj, 1));
        printf("%s\n", browserHistoryBack(obj, 1));

        browserHistoryFree(obj);
        return 0;
}