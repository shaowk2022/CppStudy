#include <stdlib.h>
#include "LinkLists.h"

bool InitList(LinkList* L){
    L = (LNode*)malloc(sizeof(LNode));
    if(L == NULL){
        LOG("init failed.");
        return false;  // 内存分配失败
    }
    (*L)->next = NULL;
    return true;
}
bool IsEmpty(LinkList L){
    return L->next == NULL;
}
