/**
 * @brief 一个银行例子，帮助理解互斥锁
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int id;
    int balance;
    pthread_mutex_t mutex;  // 每个账户都有自己的锁, 细粒度锁
} Account;

Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};  // 账户1
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // 全局互斥锁静态初始化

// 取钱
int withdraw(Account* acct, int money) {
    // 对共享资源的访问需要加锁
    pthread_mutex_lock(&(acct->mutex));
    if (acct->balance < money) {
        return 0;
    }
    sleep(1);  // 模拟取钱的时间, 提高出现线程调度的可能性
    acct->balance -= money;
    pthread_mutex_unlock(&(acct->mutex));  // 释放锁
    printf("%lu: withdraw %d\n", pthread_self(), money);
    return money;  // 返回取出的钱数
}

void* start_routine(void* args) {
    withdraw(&acct1, 100);
    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, start_routine, NULL);
    pthread_create(&t2, NULL, start_routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // 打印账号的余额
    printf("balance: %d\n", acct1.balance);
    return 0;
}
