/*
 * =====================================================================================
 *
 *       Filename:  cond.c
 *
 *    Description:  条件变量使用
 *
 *        Version:  1.0
 *        Created:  2020-01-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct node {
        int num;
        struct node *next;
} node_t;

node_t *head = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//消费者线程
void *consume(void *arg) {
        node_t *tmp;
        while (1) {
                //加锁
                pthread_mutex_lock(&mutex); //对临界变量加锁
                if (head == NULL)           //如果头部指向空，等待
                        pthread_cond_wait(&cond, &mutex);
                tmp = head;        //将要删除的节点赋值给中间值，然后头指针指向下一个
                head = head->next; //
                //解锁
                pthread_mutex_unlock(&mutex);
                //消费tmp节点
                printf("consum:%d\n", tmp->num);
                free(tmp);
                tmp = NULL;
                sleep(rand() % 5);
        }
}

//生产者线程
void *product(void *arg) { // 函数的格式void *(*start_routine) (void *)，返回值是指针，参数也是
        node_t *n;
        while (1) {
                //生产一个新的节点
                n = (node_t *)malloc(sizeof(node_t));
                n->num = rand() % 1000 + 1;
                printf("product:%d\n", n->num);
                //加锁
                pthread_mutex_lock(&mutex);
                //将新节点放入到链表的头部
                n->next = head;
                head = n;
                //解锁
                pthread_mutex_unlock(&mutex);
                //通知消费者
                pthread_cond_signal(&cond);
                sleep(rand() % 5);
        }
}

int main() {
  pthread_t pid, cid;
        //设置随机数的种子
        srand(time(NULL));
        //创建两个线程，用于生产者和消费者
        pthread_create(&pid, NULL, product, NULL); //创建线程后即执行该线程
        pthread_create(&cid, NULL, consume, NULL); //参数含义是（存放ID的缓存区，NULL缺省属性，线程的执行函数，函数的唯一参数）
        //等待线程的汇合
        pthread_join(pid, NULL);
        pthread_join(cid, NULL);
        //销毁mutex锁
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        return 0;
}
