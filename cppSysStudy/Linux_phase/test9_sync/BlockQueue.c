#include "BlockQueue.h"
#include <error.h>
#include <memory.h>
#include <stdlib.h>

BlockQueue* BlockQueue_create(void) {
    BlockQueue* q = (BlockQueue*)malloc(sizeof(BlockQueue));
    if (q == NULL) {
        error(1, -1, "malloc failed");
        return NULL;
    }
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
    memset(q->elements, 0, MAXLEN * sizeof(E));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    return q;
}
void BlockQueue_destroy(BlockQueue* q) {
    if (q == NULL) {
        return;
    }
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
    free(q);
    q = NULL;
}
void BlockQueue_push(BlockQueue* q, E e) {
    // 获取锁
    pthread_mutex_lock(&q->mutex);
    while (q->size == MAXLEN) {
        // 队列满，等待非满条件变量
        pthread_cond_wait(&q->not_full, &q->mutex);  // 这里会释放锁，并陷入阻塞，函数返回时会再次获取锁
        // 函数返回时，只能说明cond曾经成立过，现在是否成立不确定，需要再次检查，if改为while
        // 如果返回时not_full依然成立，在下一次循环时while会因为条件不成立而退出
    }
    // 队列不满，插入元素
    q->elements[q->rear] = e;
    q->rear = (q->rear + 1) % MAXLEN;
    q->size++;
    // 非空条件变量not_empty成立
    pthread_cond_signal(&q->not_empty);  // 唤醒一个等待非空条件变量的线程, 该线程就绪但不执行，因为锁未释放
    // 释放锁
    pthread_mutex_unlock(&q->mutex);
}
E BlockQueue_pop(BlockQueue* q) {
    pthread_mutex_lock(&q->mutex);
    // 判断是否为空
    while (q->size == 0) {
        // 队列空，等待非空条件变量
        pthread_cond_wait(&q->not_empty, &q->mutex);  // 返回时需再次检查队列是否为空，使用while
    }  // 队列非空，且获取锁成功

    // 取出元素
    E e = q->elements[q->front];
    q->front = (q->front + 1) % MAXLEN;
    q->size--;
    // 非满条件变量成立
    pthread_cond_signal(&q->not_full);  // 唤醒一个等待非满条件变量的线程
    // 释放锁
    pthread_mutex_unlock(&q->mutex);
    return e;
}
E BlockQueue_peek(BlockQueue* q) {
    // 获取锁
    pthread_mutex_lock(&q->mutex);
    // 判断是否为空
    while (q->size == 0) {
        // 队列空，等待非空条件变量
        pthread_cond_wait(&q->not_empty, &q->mutex);  // 返回时需再次检查队列是否为空，使用while
    }  // 队列非空，且获取锁成功

    // 访问对头元素的值
    E retval = q->elements[q->front];

    // 释放锁
    pthread_mutex_unlock(&q->mutex);

    return retval;
}
bool BlockQueue_is_empty(BlockQueue* q) {
    // 使用锁机制
    pthread_mutex_lock(&q->mutex);
    bool is_empty = (q->size == 0);
    pthread_mutex_unlock(&q->mutex);
    return is_empty;
}
bool BlockQueue_is_full(BlockQueue* q) {
    // 判断时，保证不被其他线程修改，使用锁
    pthread_mutex_lock(&q->mutex);
    bool is_full = (q->size == MAXLEN);
    pthread_mutex_unlock(&q->mutex);
    return is_full;
}