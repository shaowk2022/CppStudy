#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int threadnums)
    : isstop(false) {
    for (size_t i = 0; i < threadnums; i++) {
        // emplace是在vector容器中构造线程对象，避免额外的拷贝操作
        workers.emplace_back(
            [this]() {
                this->worker();  // 调用ThreadPool的worker函数
            });
    }
}

ThreadPool::~ThreadPool() {
    // 加锁，更改停止标识
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        isstop = true;
    }
    // 通知所有阻塞中的线程
    cv.notify_all();
    // 确保每个线程执行完成后结束(加入到主线程)
    for (std::thread& thread : workers) {
        thread.join();
    }
}

void ThreadPool::worker() {
    while (true) {
        // 定义任务
        std::function<void()> task;

        // 从队列中取得一个任务
        {
            std::unique_lock<std::mutex> lock(this->mtx);
            // wait内的条件为真时，继续执行，这里的条件是“线程终止或队列非空”
            this->cv.wait(lock, [this]() {
                return this->isstop || !this->myque.empty();
            });
            // 线程已停止或队列为空，则返回
            if(this->isstop && this->myque.empty()) return;
            task = std::move(this->myque.front());
            this->myque.pop();
        }

        // 执行任务
        task();
    }
}
