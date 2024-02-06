#include <stdio.h>
#include "SqLists.h"

void run_app(){
    StaticSqList SL;
    InitStaticSqList(&SL);
    // PrintStaticSqList(SL);
    // PRINT_LISTS(SL);
    puts("=======================");
    SqList L;
    InitSqList(&L, 10);
    // PrintSqLists(L);
    // PRINT_LISTS(L);
    puts("============插入5个元素===========");
    for (int i = 0; i < 5; i++)
    {
        StaticSqListInsert(&SL, i + 1, i + 1);
        SqListInsert(&L, i + 1, i + 1);
    }
    StaticSqListInsert(&SL, 2, 10) ? LOG("success") : LOG("failed");
    SqListInsert(&L, 4, 20) ? LOG("success") : LOG("failed");
    puts("============插入后===========");
    PRINT_LISTS(SL);
    PRINT_LISTS(L);
    puts("============删除后===========");
    int e = 0;
    StaticSqListDelete(&SL, 2, &e) ? LOG("success") : LOG("failed");
    printf("StaticSqListDelete 删除：%d\n", e);
    SqListDelete(&L, 4, &e) ? LOG("success") : LOG("failed");
    printf("SqListDelete       删除：%d\n", e);
    PRINT_LISTS(SL);
    PRINT_LISTS(L);
    puts("============按位查找===========");
    printf("StaticSqListGetElemByPos(SL, 2): %d\n", StaticSqListGetElemByPos(SL, 2));
    printf("SqListGetElemByPos(L, 4)       : %d\n", SqListGetElemByPos(L, 4));
    puts("============按值查找===========");
    printf("StaticSqListGetElemByVal(SL, 1): %d\n", StaticSqListGetElemByVal(SL, 1));
    printf("SqListGetElemByVal(L, 3)       : %d\n", SqListGetElemByVal(L, 3));
}

int main(){
    
    run_app();

    return 0;
}