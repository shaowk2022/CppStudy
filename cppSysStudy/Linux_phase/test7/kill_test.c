#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        error(1, 0, "Usage: %s signo pid ...\n", argv[0]);
    }
    int signo;
    // 把字符串形式输入的数字读取为int型数字
    sscanf(argv[1], "%d", &signo);
    for (size_t i = 2; i < argc; i++) {
        pid_t pid;
        sscanf(argv[i], "%d", &pid);
        if (kill(pid, signo) == -1) {
            // 0表示不退出程序
            error(0, errno, "kill (%d, %d)\n", pid, signo);
        }
    }

    return 0;
}