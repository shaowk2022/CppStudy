#include <stdlib.h>

#include "LinkStack.h"

bool InitLinkStack(LinkStack* LS){
    *LS = (LinkStack)malloc(sizeof(LinkNode));
    if(LS == NULL)
        return false; // 内存分配失败
    (*LS)->next = NULL; // 栈顶指针为NULL表示空
    return true;
}

bool isEmpty(LinkStack LS){
    return LS->next == NULL;
}

bool Push(LinkStack* LS, int e){
    // 不存在栈满的情况，无需判断
    LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode)); // 新元素分配空间
    newNode->data = e;
    newNode->next = (*LS)->next; // 新结点链接在原结点之后
    (*LS)->next = newNode; // 原结点的next指针作为栈顶指针
    return true;
}

bool Pop(LinkStack* LS, int* e){
    if(isEmpty(*LS))
        return false; // 栈空
    *e = (*LS)->next->data;
    // 对比单链表(左边表头/栈顶，右边表尾/栈底) ->[]->[]->[]
    // 栈底的next指向的是最新的栈顶结点
    LinkNode* tmp = (*LS)->next;
    (*LS)->next = tmp->next;
    free(tmp);
    return true;
}

bool GetTop(LinkStack LS, int* e){
    if(LS->next == NULL || LS == NULL)
        return false; // 栈空
    *e = LS->next->data;
    return true;
}

const char* Destroy(LinkStack* LS){
    if(*LS == NULL)
        return "链栈当前已经为空";  // 已空，无需销毁
    while ((*LS)->next != NULL)
    {
        LinkNode* tmp = (*LS)->next;
        (*LS)->next = tmp->next;
        free(tmp);
    }
    // 释放链栈的头结点
    free(*LS);
    // 将指向头节点的指针也置空，避免悬挂指针
    *LS = NULL;
    return "链栈销毁成功";
}