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

typedef struct node {
        char *url;
        struct node *next;
        struct node *prev;
} Node;

typedef struct browserHistory {
        Node *node;
} BrowserHistory;

BrowserHistory *browserHistoryCreate(char *homepage) {
        // strlen(homepage);
        BrowserHistory *obj = (BrowserHistory *)malloc(sizeof(BrowserHistory));
        obj->node = (Node *)malloc(sizeof(Node));
        obj->node->url = (char *)malloc(MAX_LENGTH * sizeof(char));
        strncpy(obj->node->url, homepage, strlen(homepage) + 1);
        obj->node->next = NULL;
        obj->node->prev = NULL;
        return obj;
}

void browserHistoryVisit(BrowserHistory *obj, char *url) {
        printf("visit %s\n", url);
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->url = (char *)malloc(MAX_LENGTH * sizeof(char));
        strncpy(newNode->url, url, strlen(url) + 1);
        newNode->next = NULL;
        newNode->prev = obj->node;

        // clear tails
        Node *p0 = obj->node->next;
        Node *p1 = obj->node;
        while (p0) {
                p1 = p0;
                p0 = p0->next;
                free(p1->url);
                free(p1);
        }
        obj->node->next = newNode;
        obj->node = newNode;
}

char *browserHistoryBack(BrowserHistory *obj, int steps) {
        int n = steps;
        Node *ptr0 = obj->node->prev;
        Node *ptr1 = obj->node;
        while (n) {
                if (ptr0 == NULL) {
                        break;
                }
                ptr1 = ptr0;
                ptr0 = ptr0->prev;
                n--;
        }
        obj->node = ptr1;
        return ptr1->url;
}

char *browserHistoryForward(BrowserHistory *obj, int steps) {
        int n = steps;
        Node *ptr0 = obj->node->next;
        Node *ptr1 = obj->node;

        while (n) {
                if (ptr0 == NULL) {
                        break;
                }
                ptr1 = ptr0;
                ptr0 = ptr0->next;
                n--;
        }
        obj->node = ptr1;
        return ptr1->url;
}

void browserHistoryFree(BrowserHistory *obj) {
        // back to head
        Node *ptr0 = obj->node->prev;
        Node *ptr1 = obj->node;
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
        free(obj);
}

int main() {

        BrowserHistory *obj = browserHistoryCreate("root");

        browserHistoryVisit(obj, "a");
        browserHistoryVisit(obj, "b");
        browserHistoryVisit(obj, "c");
        printf("%s\n", browserHistoryBack(obj, 1));
        printf("%s\n", browserHistoryBack(obj, 1));
        printf("%s\n", browserHistoryForward(obj, 1));

        browserHistoryFree(obj);
        return 0;
}