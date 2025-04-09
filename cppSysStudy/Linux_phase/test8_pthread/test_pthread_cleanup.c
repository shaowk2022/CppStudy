#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  // malloc
#include <sys/types.h>
#include <unistd.h>

void cleanup(void* args) {
    char* msg = (char*)args;
    printf("cleanup: %s\n", msg);
}

void* start_routine(void* args) {
    // 注册线程清理函数
    pthread_cleanup_push(cleanup, "thread cleanup1");
    pthread_cleanup_push(cleanup, "thread cleanup2");
    pthread_cleanup_push(cleanup, "thread cleanup3");

    pthread_cleanup_pop(1);  // cleanup3先出栈(被执行)
    pthread_cleanup_pop(0);  // cleanup2出栈(不执行)
    sleep(3);
    printf("thread %lu is running...\n", pthread_self());

    pthread_exit(NULL);  // 子线程退出，调用剩余的清理函数cleanup1
    // 后面的代码不会被执行
    pthread_cleanup_pop(0);  // push和pop的数量必须对应，否则编译报错
}

int main(int argc, char const* argv[]) {
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err) {
        error(1, err, "pthread_create error.\n");
    }
    err = pthread_join(tid, NULL);  // 等待子线程结束
    if (err) {
        error(1, err, "pthread_join error.\n");
    }
    return 0;
}
