/**
 * @brief 使用线程池实现生产者消费者模型，演示条件变量的使用
 */

#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "BlockQueue.h"

typedef struct {
    int nums;            // 线程池中线程数量
    pthread_t* threads;  // 保存线程池中线程的ID，用堆保存，所以用指针
    BlockQueue* q;       // 阻塞队列
} ThreadPool;

void* start_routine(void* args) {
    ThreadPool* threadpool = (ThreadPool*)args;
    pthread_t pid = pthread_self();  // 获取当前线程的ID
    while (1) {
        // 从阻塞队列中获取任务
        E task_id = BlockQueue_pop(threadpool->q);  // 没有任务时，pop中的cond_wait()阻塞

        // 判断是否为退出任务
        if (task_id == -1) {
            printf("Thread %ld is exiting\n", pid);
            pthread_exit(NULL);  // 退出线程
        }

        // 执行任务
        printf("Thread %ld is processing task %d\n", pid, task_id);
        sleep(1);  // 模拟任务处理时间
        // 处理完成，打印信息
        printf("Thread %ld finished task %d\n", pid, task_id);
    }
    return NULL;
}

ThreadPool* threadpool_create(int n) {
    ThreadPool* threadpool = (ThreadPool*)malloc(sizeof(ThreadPool));
    threadpool->nums = n;
    threadpool->threads = (pthread_t*)malloc(n * sizeof(pthread_t));  // 在堆上存放n个线程ID
    threadpool->q = BlockQueue_create();

    // 创建n个线程
    for (size_t i = 0; i < n; i++) {
        pthread_create(threadpool->threads + i, NULL, start_routine, (void*)threadpool);
    }

    return threadpool;
}

void threadpool_destroy(ThreadPool* pool) {
    if (pool == NULL)
        error(1, -1, "threadpool_destroy: pool is NULL");
    // 依次销毁
    BlockQueue_destroy(pool->q);
    free(pool->threads);
    free(pool);
    pool = NULL;
}

int main() {
    // 1.创建线程池并初始化
    int n = 8;  // 线程数目
    ThreadPool* pool = threadpool_create(n);

    // 2.主线程生产任务
    for (size_t i = 0; i < 100; i++) {
        BlockQueue_push(pool->q, i + 1);
    }

    sleep(5);

    // 3. 等待线程结束，退出线程池
    // 3.1 暴力退出，不是所有任务都可以被执行【一般不使用】
    // for (size_t i = 0; i < pool->nums; i++) {
    //     pthread_cancel(pool->threads[i]);  // 发送取消请求
    // }

    // 3.2 优雅退出，将退出任务标记为-1，添加到队列中，刚好利用了FIFO的特性
    for (size_t i = 0; i < pool->nums; i++) {
        BlockQueue_push(pool->q, -1);  // 添加退出任务
    }

    for (size_t i = 0; i < pool->nums; i++) {
        pthread_join(pool->threads[i], NULL);  // 等待线程结束
    }

    // 4. 销毁线程池
    threadpool_destroy(pool);

    return 0;
}