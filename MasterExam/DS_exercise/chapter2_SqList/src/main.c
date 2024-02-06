#include <stdio.h>
#include "SqLists.h"

void run_app(){
    StaticSqList SL;
    InitStaticSqList(&SL);
    // PrintStaticSqList(SL);
    // PRINT_LISTS(SL);
    puts("\n=======================");
    SqList L;
    InitSqList(&L, 10);
    // PrintSqLists(L);
    // PRINT_LISTS(L);
    puts("\n============插入5个元素===========");
    for (int i = 0; i < 5; i++)
    {
        StaticSqListInsert(&SL, i + 1, i + 1);
        SqListInsert(&L, i + 1, i + 1);
    }
    StaticSqListInsert(&SL, 2, 10) ? LOG("success") : LOG("failed");
    SqListInsert(&L, 4, 20) ? LOG("success") : LOG("failed");
    puts("\n============插入后===========");
    PRINT_LISTS(SL);
    PRINT_LISTS(L);
    puts("\n============删除后===========");
    int e = 0;
    StaticSqListDelete(&SL, 2, &e) ? LOG("success") : LOG("failed");
    printf("StaticSqListDelete 删除：%d\n", e);
    SqListDelete(&L, 4, &e) ? LOG("success") : LOG("failed");
    printf("SqListDelete       删除：%d\n", e);
    PRINT_LISTS(SL);
    PRINT_LISTS(L);
}

int main(){
    
    run_app();

    return 0;
}