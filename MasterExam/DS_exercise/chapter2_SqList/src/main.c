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
    StaticSqListInsert(&SL, 2, 10) ? puts("success") : puts("failed");
    SqListInsert(&L, 4, 20) ? puts("success") : puts("failed");
    puts("\n============插入后===========");
    PRINT_LISTS(SL);
    PRINT_LISTS(L);
}

int main(){
    
    run_app();

    return 0;
}