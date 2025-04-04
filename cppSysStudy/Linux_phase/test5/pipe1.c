#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 256

int main(int argc, char* argv[]){
    // 向pipe1写入
    int fdw = open("pipe1", O_WRONLY);
    if(fdw == -1){
        error(1, errno, "open pipe1 failed.\n");
    }
    // 从pipe2读出
    int fdr = open("pipe2", O_RDONLY);
    if(fdr == -1){
        error(1, errno, "open pipe2 failed.\n");
    }

    puts("Link Established.");

    char recvline[MAXLINE];
    char sendline[MAXLINE];

    // 从stdin(键盘)读取一行行的读取
    while (fgets(sendline, MAXLINE, stdin) != NULL)
    {
        write(fdw, sendline, strlen(sendline));  // 发消息
        read(fdr, recvline, MAXLINE); // 读消息
        printf("recv from p2:【%s】\n", recvline);
    }

    close(fdr);
    close(fdw);

    return 0;
}