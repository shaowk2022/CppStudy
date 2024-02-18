#include <stdlib.h>
#include "LinkLists.h"

bool InitList(LinkList* L){
    *L = (LNode*)malloc(sizeof(LNode));
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

bool ListInsert(LinkList* L, int pos, int e){
    if(pos < 1)
        return false;
    LNode* target = *L;  // 临时指针指向头结点
    int cur_pos = 0;    // 临时指针指向的结点位序，0即为头结点
    while(target != NULL && cur_pos < pos - 1){  // 循环找到pos的前一个结点
        target = target->next;
        cur_pos++;
    }
    if(target == NULL)  // pos位置不合法
        return false;
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = target->next;
    target->next = s;
    return true;

}
