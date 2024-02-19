#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkList.h"

bool InitDLinkList(DLinkList* L){
    *L = (DNode*)malloc(sizeof(DNode));
    if(*L == NULL)
        return false;
    (*L)->data = 0;
    (*L)->prior = NULL;
    (*L)->next = NULL;
    return true;
}

bool IsEmpty(DLinkList L){
    return L->next == NULL;
}

bool InsertNextDNode(DNode* p, int e){
    if(p == NULL)
        return false;
    DNode* NewDNode = (DNode*)malloc(sizeof(DNode));
    NewDNode->data = e;
    // 注意: 以下4行赋值相当于改变指针的指向，且前两句顺序不能调换
    NewDNode->next = p->next;
    if(p->next != NULL) // 如果p不是尾结点，则更改下一个结点的前驱
        p->next->prior = NewDNode;
    p->next = NewDNode;
    NewDNode->prior = p;
    return true;
}

void PrintElem(DLinkList L){
    puts("打印双链表元素:");
    DNode* tmp = L->next;
    while (tmp != NULL)
    {
        printf("%d\t", tmp->data);
        tmp = tmp->next;
    }
    puts("\n打印结束.");
}

bool DeleteNextDNode(DNode* p){
    if(p == NULL)
        return false;
    DNode* target = p->next;
    if(target == NULL)
        return false;  // p是最后一个结点
    p->next = target->next;
    if(target->next != NULL) 
        // 待删结点存在后继结点，改变其前向指针
        target->next->prior = p;
    free(target);
    return true;
}

void DestroyDLinkList(DLinkList* L){
    // 从前向后循环释放各个结点
    while ((*L)->next != NULL)
        DeleteNextDNode(*L);
    free(L);
    L = NULL; // 头指针置空
}

void DLinkListTraverse(DNode* p){
    // 后向遍历
    DNode* p1 = p;
    while (p1 != NULL)
    {
        // 对当前结点进行处理，如打印
        p1 = p1->next;
    }
#if 0
    // 前向遍历
    DNode* p2 = p;
    while (p2 != NULL)
    {
        // 对当前结点进行处理，如打印
        p2 = p2->prior;
    }

    // 前向遍历并跳过头结点
    DNode* p3 = p;
    while (p3->prior != NULL)
    {
        // 对当前结点进行处理，如打印
        p3 = p3->prior;
    }
#endif
    
}