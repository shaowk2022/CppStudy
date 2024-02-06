#include <stdlib.h>
#include <stdio.h>
#include "SqLists.h"

void InitStaticSqList(StaticSqList* L){
    for(int i = 0; i < MaxLength; i++){
        L->data[i] = 0;
    }
    L->length = 0;
}

void PrintStaticSqList(StaticSqList L){
    puts("the value of Lists: ");
    for(int i = 0; i < L.length; i++){
        printf("%d\t", L.data[i]);
    }
    puts("");
}


void InitSqList(SqList* L, int MaxSize){
    L->data = (int*)malloc(sizeof(L->data) * MaxSize);
    for(int i = 0; i < MaxSize; i++){
        L->data[i] = 0;
    }
    L->length = 0;
    L->MaxSize = MaxSize;
}

void PrintSqLists(SqList L){
    puts("the value of Lists: ");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d\t", L.data[i]);
    }
    puts("");
}

bool StaticSqListInsert(StaticSqList* L, int pos, int e){
    if(pos < 1 || pos > (L->length + 1)){
        return false;
    }
    if(L->length >= MaxLength)
        return false;
    for(int i = L->length; i >= pos; i--){
        L->data[i] = L->data[i - 1];
    }
    L->data[pos - 1]  = e;
    L->length++;
    return true;
}

bool SqListInsert(SqList* L, int pos, int e){
    if(pos < 1 || pos > (L->length + 1)){
        return false;
    }
    if(L->length >= L->MaxSize)
        return false;
    for(int i = L->length; i >= pos; i--){
        L->data[i] = L->data[i - 1];
    }
    L->data[pos - 1] = e;
    L->length++;
    return true;
}

bool StaticSqListDelete(StaticSqList* L, int pos, int* e){
    if(pos < 1 || pos > L->length){
        return false;
    }
    *e = L->data[pos - 1];
    for(int i = pos; i < L->length; i++){
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return true;
}

bool SqListDelete(SqList* L, int pos, int* e){
    if(pos < 1 || pos > L->length){
        return false;
    }
    *e = L->data[pos - 1];
    for(int i = pos; i < L->length; i++){
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return true;
}