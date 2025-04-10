#ifndef __BLOCK_QUEUE_H__
#define __BLOCK_QUEUE_H__

#include <pthread.h>
#include <stdbool.h>

#define MAXLEN 1024

typedef int E;  // 元素类型

// 用循环数组实现阻塞队列
typedef struct {
    E elements[MAXLEN];  // 元素数组
    int front;           // 队头下标
    int rear;            // 队尾下标
    int size;            // 当前元素个数

    pthread_mutex_t mutex;     // 互斥锁保护条件变量cond
    pthread_cond_t not_empty;  // 非空条件变量
    pthread_cond_t not_full;   // 非满条件变量

} BlockQueue;

// API
BlockQueue* BlockQueue_create(void);
void BlockQueue_destroy(BlockQueue* q);
void BlockQueue_push(BlockQueue* q, E e);
E BlockQueue_pop(BlockQueue* q);
E BlockQueue_peek(BlockQueue* q);         // 查看队头元素
bool BlockQueue_is_empty(BlockQueue* q);  // 判断队列是否为空
bool BlockQueue_is_full(BlockQueue* q);   // 判断队列是否为满

#endif  // __BLOCK_QUEUE_H__