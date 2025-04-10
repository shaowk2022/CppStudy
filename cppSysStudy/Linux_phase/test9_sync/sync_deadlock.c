/**
 * @brief 转账案例，演示死锁
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    char name[20];  // 账户名
    int id;         // 账户ID
    int balance;
    pthread_mutex_t mutex;  // 每个账户都有自己的锁, 细粒度锁
} Account;

Account acct1 = {"Tom", 1, 1000, PTHREAD_MUTEX_INITIALIZER};   // 账户1
Account acct2 = {"Jerry", 2, 100, PTHREAD_MUTEX_INITIALIZER};  // 账户2
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;      // 全局互斥锁静态初始化

// 转账
int transfer(Account* acctA, Account* acctB, int money) {
#if 0
    // 破坏循环等待条件，按照id从小到大获取锁，避免死锁
    if (acctA->id < acctB->id) {
        pthread_mutex_lock(&acctA->mutex);  // 锁定账户A
        sleep(1);                           // 模拟转账延迟, 增加死锁调度的概率
        pthread_mutex_lock(&acctB->mutex);  // 锁定账户B
    } else {
        pthread_mutex_lock(&acctB->mutex);  // 锁定账户B
        sleep(1);                           // 模拟转账延迟, 增加死锁调度的概率
        pthread_mutex_lock(&acctA->mutex);  // 锁定账户A
    }
#endif

#if 0
start:
    // 破坏不能抢占条件，避免死锁
    pthread_mutex_lock(&acctA->mutex);               // 锁定账户A
    sleep(1);                                        // 模拟转账延迟, 增加死锁调度的概率
    int err = pthread_mutex_trylock(&acctB->mutex);  // 尝试锁定账户B
    if (err) {
        pthread_mutex_unlock(&acctA->mutex);  // 无法锁定B，则释放A的锁, 破坏不能抢占条件
        sleep(1);                             // 1s后重试
        goto start;
    }
#endif

    // 破坏持有并等待条件，避免死锁
    // 把对A和B的加锁看做是一个原子操作
    pthread_mutex_lock(&global_mutex);    // 锁定全局锁
    pthread_mutex_lock(&acctA->mutex);    // 锁定账户A
    sleep(1);                             // 模拟转账延迟, 增加死锁调度的概率
    pthread_mutex_lock(&acctB->mutex);    // 锁定账户B
    pthread_mutex_unlock(&global_mutex);  // 解锁全局锁

    if (acctA->balance < money) {
        pthread_mutex_unlock(&acctA->mutex);
        pthread_mutex_unlock(&acctB->mutex);  // 解锁账户
        return 0;                             // 余额不足
    }

    acctA->balance -= money;
    acctB->balance += money;

    pthread_mutex_unlock(&acctA->mutex);  // 解锁账户A
    pthread_mutex_unlock(&acctB->mutex);  // 解锁账户B
    return money;                         // 实际转账金额
}

// 线程函数1
void* start_routine1(void* args) {
    int money = (int)args;
    int ret = transfer(&acct1, &acct2, money);  // acct1转账给acct2
    printf("%s -> %s: %d\n", acct1.name, acct2.name, ret);
    return NULL;
}

// 线程函数2
void* start_routine2(void* args) {
    int money = (int)args;
    int ret = transfer(&acct2, &acct1, money);  // acct2转账给acct1
    printf("%s -> %s: %d\n", acct2.name, acct1.name, ret);
    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, start_routine1, (void*)900);
    pthread_create(&t2, NULL, start_routine2, (void*)100);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);  // 阻塞，等待线程结束

    // 打印账户余额
    printf("%s: %d\n", acct1.name, acct1.balance);
    printf("%s: %d\n", acct2.name, acct2.balance);

    return 0;
}
