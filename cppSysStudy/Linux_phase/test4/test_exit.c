#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef void (*VOIDFUNPTR)(void);

void print(void){
    puts("I am going to die.");
}

void print_wstatue(int status){
    if(WIFEXITED(status)){
        int exit_code = WEXITSTATUS(status);
    }
    
}

int main(void){
    // 调用ateixt()注册退出函数
    VOIDFUNPTR func = print;
    int err = atexit(func);
    if(err){
        error(1, 0, "atexit\n");
    }
    
    puts("hello world");
    exit(123);  // exit调用atexit()注册的函数func
    return 0;
}