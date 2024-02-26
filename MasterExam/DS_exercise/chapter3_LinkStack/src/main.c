#include <stdio.h>

#include "LinkStack.h"

void run_LinkStack_app(){
    LinkStack LS;
    int ret = 0;

    InitLinkStack(&LS);
    printf("%s\n", isEmpty(LS) ? "NULL" : "Not NULL");

    Push(&LS, 1);
    Push(&LS, 2);
    Push(&LS, 3);
    printf("%s\n", isEmpty(LS) ? "NULL" : "Not NULL");

    GetTop(LS, &ret);
    printf("Top: %d\n", ret);  // 3

    Pop(&LS, &ret);
    printf("%d\n", ret);
    Pop(&LS, &ret);
    printf("%d\n", ret);
    printf("%s\n", isEmpty(LS) ? "NULL" : "Not NULL");

    GetTop(LS, &ret);
    printf("Top: %d\n", ret);  // 1

    Pop(&LS, &ret);
    printf("%d\n", ret);
    printf("%s\n", isEmpty(LS) ? "NULL" : "Not NULL");

    GetTop(LS, &ret);
    printf("Top: %d\n", ret);  // 1, 这里的ret为最后一次出栈的值

    printf("%s \n", Destroy(&LS));
    printf("%s \n", Destroy(&LS));
}

int main(){
    run_LinkStack_app();
    return 0;
}