#include <iostream>

#include "ThreadPool.hpp"

int main() {
    ThreadPool mypool(4);
    // 创建20个任务
    for (size_t i = 0; i < 20; i++) {
        auto rsfuture = mypool.enques(
            [](int a, int b) -> int {
                std::cout << "当前线程id: " << std::this_thread::get_id() << std::endl;
                return a + b;
            },
            10 * i, 10 * i);
        std::cout << "thread rs: " << rsfuture.get() << std::endl;
    }

    return 0;
}