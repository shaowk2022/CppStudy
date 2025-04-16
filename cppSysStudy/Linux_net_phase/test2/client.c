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

void handle_sigint(int signum, siginfo_t* info, void* args) {
    int sockfd = info->si_fd;  // 从信号中获取socket描述符
    if (sockfd != -1) {
        printf("Closing socket: %d\n", sockfd);
        close(sockfd);  // 关闭socket
    } else {
        printf("No socket to close.\n");
    }
    exit(0);  // 正常退出程序
}

int main(int argc, char const* argv[]) {
    // 注册信号处理函数，用于关闭socket
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;         // 使用带额外信息的处理函数
    sa.sa_sigaction = handle_sigint;  // 指向信号处理函数
    sigaction(SIGINT, &sa, NULL);     // 绑定SIGINT信号和sigaction

    // 申请一个TCP的socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");

    // 服务器的网络地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));  // 清空内容
    server_addr.sin_family = AF_INET;              // IPv4
    server_addr.sin_addr.s_addr = inet_addr("192.168.141.128");
    server_addr.sin_port = htons(8888);

    // 连接服务器
    int ret = connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "connect");
    puts("Connected to server!");

    char buffer[1024];

    while (1) {
        strcpy(buffer, "hello server");
        send(clientfd, buffer, strlen(buffer), 0);  // 发送数据
        printf("Sent: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));  // 清空buffer
        sleep(2);                           // 等待2秒
    }

    return 0;
}
