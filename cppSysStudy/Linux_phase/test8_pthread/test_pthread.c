#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void print_ids(const char* prefix) {
    printf("%s: ", prefix);
    printf("pid = %d, ppid = %d, ", getpid(), getppid());
    printf("tid = %lu\n", pthread_self());
}

void* start_routine(void* args) {
    print_ids("new_thread");
    return NULL;
}

int main(int argc, char const* argv[]) {
    // pthread_t id = pthread_self();

    // 主线程
    print_ids("main");

    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err) {
        error(1, err, "pthread_create error.\n");
    }

    printf("main: new_thread id = %lu\n", tid);

    pthread_join(tid, NULL);  // 子线程运行结束后再终止主线程

    return 0;
}
