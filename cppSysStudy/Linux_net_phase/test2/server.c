#define _POSIX_C_SOURCE 200809L  // Enable POSIX features

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>  // for exit()
#include <string.h>  // for memset()
#include <sys/socket.h>
#include <unistd.h>  // for sleep()

#define ERROR_CHECK(ret, num, msg) \
    if (ret == num) {              \
        perror(msg);               \
        return -1;                 \
    }

// 信号处理函数
void handle_sigint(int signum, siginfo_t* info, void* args) {
    // 从信号中获取socket描述符
    int sockfd = info->si_fd;
    if (sockfd != -1) {
        printf("Closing socket: %d\n", sockfd);
        close(sockfd);  // 关闭socket
    } else {
        printf("No socket to close.\n");
    }
    exit(0);  // 正常退出程序
}

int main(int argc, char const* argv[]) {
    // 注册信号处理函数用于close socket
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;         // 使用带额外信息的处理函数
    sa.sa_sigaction = handle_sigint;  // 指向信号处理函数
    sigaction(SIGINT, &sa, NULL);     // 绑定SIGINT信号和sigaction

    // 申请一个TCP的socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listenfd, -1, "socket");

    // 填充一个网络地址
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));                       // 清空内容
    addr.sin_family = AF_INET;                            // IPv4
    addr.sin_port = htons(8888);                          // 端口号
    addr.sin_addr.s_addr = inet_addr("192.168.141.128");  // IP地址

    // 把socket和地址绑定, &addr强转一下，否则有warning
    int ret = bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");

    // 开始监听, 至多10个连接
    ret = listen(listenfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    printf("waiting for client...\n");

    // 接收连接所用的socket
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int clientfd = accept(listenfd, (struct sockaddr*)&client_addr, &addr_len);  // 获取client的socket描述符
    ERROR_CHECK(clientfd, -1, "accept");
    printf("Client connected!\n");

    char buffer[1024] = {0};  // 接收数据的缓冲区
    while (1) {
        recv(clientfd, buffer, sizeof(buffer), 0);  // 接收数据
        if (strlen(buffer) == 0) {
            printf("No data received.\n");
            sleep(2);  // 等待2秒
            continue;  // 如果没有数据，继续循环
        }
        printf("Received: %s\n", buffer);  // 打印接收到的数据
        // 清空缓冲区
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}
