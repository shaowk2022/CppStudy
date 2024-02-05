#include <stdlib.h>
#include <stdio.h>
#include "SqLists.h"

void InitStaticSqList(StaticSqList* L){
    for(int i = 0; i < MaxLength; i++){
        L->data[i] = 0;
    }
    L->length = 0;
}

void InitSqList(SqList* L, int MaxSize){
    L->data = (int*)malloc(sizeof(L->data) * MaxSize);
    for(int i = 0; i < MaxSize; i++){
        L->data[i] = 0;
    }
    L->length = 0;
    L->MaxSize = MaxSize;
}

void PrintStaticSqList(StaticSqList L){
    puts("the value of Lists: ");
    for(int i = 0; i < L.length; i++){
        printf("%d\t", L.data[i]);
    }
    puts("");
}

void PrintSqLists(SqList L){
    puts("the value of Lists: ");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d\t", L.data[i]);
    }
    puts("");
}