#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  // malloc
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    int left;
    int right;  // 区间的左右端点
} Section;

void print_ids(const char* prefix) {
    printf("%s: ", prefix);
    printf("pid = %d, ppid = %d, ", getpid(), getppid());
    printf("tid = %lu\n", pthread_self());
}

void* start_routine(void* args) {
    Section* section = (Section*)args;
    // 动态分配内存, 否则函数返回时result指向一个无效地址
    // 因为用int sum, 则在栈上的局部变量sum会在函数结束时被销毁, 线程退出时栈被销毁
    int* sum = (int*)malloc(sizeof(int));
    if (sum == NULL) {
        perror("malloc error");
        pthread_exit(NULL);
    }
    *sum = 0;  // 初始化sum
    for (size_t i = section->left; i <= section->right; i++) {
        *sum += i;
    }

    return (void*)sum;
    // pthread_exit((void*)sum);  // 线程结束时返回和
}

int main(int argc, char const* argv[]) {
    // pthread_t id = pthread_self();

    // 分别用两个线程对1-50求和、51-100求和
    pthread_t tid1, tid2;
    Section section1 = {1, 50};
    Section section2 = {51, 100};

    int err = pthread_create(&tid1, NULL, start_routine, &section1);  // 非0为错误码
    if (err) {
        error(1, err, "pthread_create error.\n");
    }

    err = pthread_create(&tid2, NULL, start_routine, &section2);
    if (err) {
        error(1, err, "pthread_create error.\n");
    }
    // 主线程等待返回结果并计算出1-100的和
    int *result1 = NULL, *result2 = NULL;
    err = pthread_join(tid1, (void**)&result1);  // join()会无限期等待，直到子线程结束
    if (err) {
        error(1, err, "pthread_join error, tid: %lu.\n", tid1);
    }
    err = pthread_join(tid2, (void**)&result2);
    if (err) {
        error(1, err, "pthread_join error, tid: %lu.\n", tid2);
    }
    printf("sum = %d + %d = %d\n", *result1, *result2, *result1 + *result2);

    free(result1);
    free(result2);             // 释放动态分配的内存
    result1 = result2 = NULL;  // 避免悬空指针
    return 0;
}
