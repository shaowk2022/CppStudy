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

bool ListInsertByPos(LinkList* L, int pos, int e){
    if(pos < 1)
        return false;

    // 无头结点情况下的插入，若是插入第一个结点需要特殊处理
    /*if(pos == 1){  // 无头节点情况下插入第一个结点
        LNode* s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;  // 头指针指向新结点
        return true;
    }*/
    
    // int cur_pos = 1;  // 没有头结点时，当前指向位置从1开始

    LNode* target = *L;  // 临时指针指向头结点
    int cur_pos = 0;    // 临时指针指向的结点位序，0即为头结点
    while(target != NULL && cur_pos < pos - 1){  // 循环找到pos的前一个结点
        target = target->next;
        cur_pos++;
    }
    // 已找到目标结点的前驱，直接使用后插操作进行插入
    /*if(target == NULL)  // pos位置不合法
        return false;
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = target->next;
    target->next = s;
    return true;*/
    return ListInsertNextNode(target, e);
}

bool ListInsertNextNode(LNode* p, int e){
    if(p == NULL)
        return false; // 目标结点不合法
    LNode* s = (LNode*)malloc(sizeof(LNode));
    if(s == NULL)
        return false; // 内存分配失败
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListInsertPriorNode(LNode* p, int e){
    // p结点前插操作转变为后插，然后修改数据域
    if(p == NULL)
        return false;
    LNode* s = (LNode*)malloc(sizeof(LNode));
    if(s == NULL)
        return false;
    s->next = p->next;
    p->next = s;
    s->data = p->data;
    p->data = e;
    return true;
}

void ListPrintElem(LinkList L){
    if(L == NULL){
        LOG("链表不存在.");
        return;
    }
    LNode* p = L->next;
    while (p != NULL)
    {
        printf("%d \t", p->data);
        p = p->next;
    }
    printf("\n");
    LOG("元素打印结束");
}