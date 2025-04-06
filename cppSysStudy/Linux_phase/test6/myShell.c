#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 256
#define MAXARGS 64

void parse_input_args(char* input, char* args[]) {
    int i = 0;
    args[i] = strtok(input, " \t\n");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    }
}

void print_args(char* args[]) {
    for (int i = 0; args[i] != NULL; i++) {
        puts(args[i]);
    }
}

void print_wstatus(int status) {
    if (WIFEXITED(status)) {  // 正常退出
        int exit_code = WEXITSTATUS(status);
        printf("exit code: %d\n", exit_code);
    } else if (WIFSIGNALED(status)) {  // 异常退出: 打印异常信号类别
        int singal_no = WTERMSIG(status);
        printf("signal number: %d\n", singal_no);
#ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
            printf("core dump.");  // 引起core dump给出提示
        }
#endif
    }
}

int main(int argc, char* argv[]) {
    while (1) {
        printf("myShell> ");
        char input[MAXLINE];
        char* args[MAXARGS];

        // 读取输入参数并解析
        fgets(input, MAXLINE, stdin);
        if(strcmp(input, "exit\n") == 0){  // 输入exit直接退出
            break;
        }
        parse_input_args(input, args);

        // print_args(args);

        // 使用子进程执行shell命令，父进程等待
        switch (fork()) {
        case -1:
            error(1, errno, "fork error.");
        case 0:
            // 子进程用execvp()执行命令, p是从环境变量里找命令，v对应args的类型
            if (execvp(args[0], args) == -1) {
                error(1, errno, "execvp error.");
            }
        default:
            // 父进程等待子进程结束
            int wstatus;
            pid_t child_pid = wait(&wstatus);
            printf("PID: %d process terminated. \n", child_pid);
            // 打印子进程的终止状态
            print_wstatus(wstatus);
        }
    }
    return 0;
}