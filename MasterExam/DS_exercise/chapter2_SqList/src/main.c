#include <stdio.h>
#include "SqLists.h"

int main(){
    StaticSqList SL;
    InitStaticSqList(&SL);
    // PrintStaticSqList(SL);
    PRINT_LISTS(SL);
    puts("\n=======================");
    SqList L;
    InitSqList(&L, 10);
    // PrintSqLists(L);
    PRINT_LISTS(L);

    return 0;
}