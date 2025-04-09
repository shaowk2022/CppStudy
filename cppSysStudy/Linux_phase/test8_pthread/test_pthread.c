#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int id;
    char name[20];
} Student;

void print_ids(const char* prefix) {
    printf("%s: ", prefix);
    printf("pid = %d, ppid = %d, ", getpid(), getppid());
    printf("tid = %lu\n", pthread_self());
}

void* start_routine(void* args) {
    print_ids("new_thread");
    // printf("args = %d\n", (int)args);

    pthread_exit(NULL);  // 线程退出
    printf("this msg will not be outputted.\n");

    Student* stu = (Student*)args;
    printf("id: %d, name: %s\n", stu->id, stu->name);  // 在子线程中访问主线程的数据stu
    return NULL;
}

int main(int argc, char const* argv[]) {
    // pthread_t id = pthread_self();

    // 主线程
    print_ids("main");
    Student stu = {1, "zhangsan"};
    pthread_t tid;
    // int err = pthread_create(&tid, NULL, start_routine, (void*)9527);
    int err = pthread_create(&tid, NULL, start_routine, (void*)&stu);  // 非0为错误码
    if (err) {
        error(1, err, "pthread_create error.\n");
    }

    // printf("main: new_thread id = %lu\n", tid);

    pthread_join(tid, NULL);  // 子线程运行结束后再终止主线程

    return 0;
}
