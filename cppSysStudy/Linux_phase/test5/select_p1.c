#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 256

int main(int argc, char* argv[]) {
    // 向pipe1写入
    int fdw = open("pipe1", O_WRONLY);
    if (fdw == -1) {
        error(1, errno, "open pipe1 failed.\n");
    }
    // 从pipe2读出
    int fdr = open("pipe2", O_RDONLY);
    if (fdr == -1) {
        error(1, errno, "open pipe2 failed.\n");
    }

    puts("Link Established.");

    char recvline[MAXLINE];
    char sendline[MAXLINE];

    fd_set mainfds;                  // 局部变量，fd_set是结构体
    FD_ZERO(&mainfds);               // 所有位清0
    FD_SET(STDIN_FILENO, &mainfds);  // 设置位图中stdin对应的文件描述符，表示想监听这一位
    int maxfds = STDIN_FILENO;
    FD_SET(fdr, &mainfds);  // 监听pipe2的读端，设置位图中fdr的那一位

    // 因为select首个参数nfds是要检查的最大文件描述符+1，所以这里确保maxfds指向最大的文件描述符
    if (fdr > maxfds) {
        maxfds = fdr;
    }

    for (;;) {
        fd_set readfds = mainfds;  // 先保存想监听的文件描述符
        // struct timeval timeout = {5, 0};  // 超时时间
        // int events = select(maxfds + 1, &readfds, NULL, NULL, &timeout);  // 返回已就绪的文件描述符个数
        int events = select(maxfds + 1, &readfds, NULL, NULL, NULL);  // 无期限等待直到有消息
        switch (events) {
        case -1:
            error(1, errno, "select");
        case 0:
            puts("TIME OUT, continue waiting ...");
            continue;  // 当前超时，继续等待
        default:
            // 打印剩余的等待时间
            // printf("timeout: sec = %ld, usec = %ld\n", timeout.tv_sec, timeout.tv_usec);
            // 有读事件就绪(但是不确定是pipe2的读还是stdin的读就绪了)
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                // STDIN_FILENO就绪，此时再读stdin一定不阻塞
                fgets(sendline, MAXLINE, stdin);
                write(fdw, sendline, strlen(sendline) + 1);  // +1是为了多传入一个用于结尾的空字符\0
            } else if (FD_ISSET(fdr, &readfds)) {
                // pipe2的读端就绪，对方来消息了，此时读管道一定不阻塞
                int nbytes = read(fdr, recvline, MAXLINE);  // 记录读取的字节数
                if (nbytes == 0) {                          // 为0说明对端(管道的写端)关闭了
                    goto end;                               // 聊天结束, 跳出for循环
                } else if (nbytes == -1) {
                    error(1, errno, "read pipe1 failed.");
                }
                printf("recv msg from p2> %s", recvline);
            }
        }
    }

end:
    close(fdr);
    close(fdw);

    return 0;
}