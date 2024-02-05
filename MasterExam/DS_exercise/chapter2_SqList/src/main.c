#include <stdio.h>
#include "SqLists.h"

int main(){
    StaticSqList SL;
    InitStaticSqList(&SL);
    PrintStaticSqList(SL);
    puts("\n=======================");
    SqList L;
    InitSqList(&L, 10);
    PrintSqLists(L);

    return 0;
}