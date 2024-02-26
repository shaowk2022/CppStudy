#include <stdio.h>

#include "SqStack.h"

void run_stack_app(){
    SqStack SS;

    InitSqStack(&SS);
    printf("%s\n", isEmpty(SS) ? "NULL" : "Not NULL");
    
    Push(&SS, 1);
    Push(&SS, 2);
    Push(&SS, 3);
    printf("%s\n", isEmpty(SS) ? "NULL" : "Not NULL");

    int ret = 0;
    Pop(&SS, &ret);
    printf("出栈第一次:%d \n", ret);
    Pop(&SS, &ret);
    printf("出栈第二次:%d \n", ret);

    GetTop(SS, &ret);
    printf("GetTop第1次:%d \n", ret);
    GetTop(SS, &ret);
    printf("GetTop第2次:%d \n", ret);

    DestroyStack(&SS);
    printf("%s\n", isEmpty(SS) ? "NULL" : "Not NULL");
}

int main(){
    run_stack_app();
    return 0;
}