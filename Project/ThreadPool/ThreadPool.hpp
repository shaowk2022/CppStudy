#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <queue>

class ThreadPool
{
public:
    ThreadPool(int threadnums);
    ~ThreadPool();

    // 添加任务到队列, ...Arg表示多个参数. 返回类型后置写法，为了好看
    template <typename F, typename ...Arg>
    auto enques(F&& f, Arg&& ...arg) -> std::future<typename std::result_of<F(Arg...)>::type>;

private:
    void worker();  // 线程的执行内容
    bool isstop;  // 标识线程池是否终止
    // 条件变量，通信线程的任务是否完成，完成则让线程进入阻塞
    std::condition_variable cv;  
    std::mutex mtx; // 互斥锁，保证线程安全
    std::vector<std::thread> workers;  // 线程池
    std::queue<std::function<void()>> myque;  // 任务队列
};

/**
 * @brief 包装用户的函数->加入到任务队列->返回执行结果
 * @note  模板函数必须放在头文件，否则链接时会找不到定义
 */
template <typename F, typename... Arg>
auto ThreadPool::enques(F&& f, Arg&&... arg) -> std::future<typename std::result_of<F(Arg...)>::type> {
    // 给函数f执行后返回的类型取个别名
    using functype = typename std::result_of<F(Arg...)>::type;

    // 生成一个智能指针(延长目标对象的生命周期)，指向一个被包装为functype()类型的task
    auto task = std::make_shared<std::packaged_task<functype()>>(
        std::bind(std::forward<F>(f), std::forward<Arg>(arg)...)  // 把函数f和参数绑定到一起，forward完美转发
    );

    // 获得future
    std::future<functype> rsfuture = task->get_future();

    // 将任务添加到队列
    {
        std::lock_guard<std::mutex> lockguard(this->mtx);
        if (this->isstop)
            throw std::runtime_error("线程池已停止，无法将任务添加到执行队列！");

        myque.emplace(
            [task]() {
                (*task)();  // 添加到队列
            });
    }

    // 通知线程执行任务
    this->cv.notify_one();

    // 返回任务的执行结果
    return rsfuture;
}

#endif // THREAD_POOL_HPP