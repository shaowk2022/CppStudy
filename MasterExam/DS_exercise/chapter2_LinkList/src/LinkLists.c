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
#if 0
    // 无头结点情况下的插入，若是插入第一个结点需要特殊处理
    /*if(pos == 1){  // 无头节点情况下插入第一个结点
        LNode* s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;  // 头指针指向新结点
        return true;
    }*/
    // int cur_pos = 1;  // 没有头结点时，当前指向位置从1开始
#endif

#if 0
    // 有头节点时
    // 1-循环找到pos的前一个结点
    LNode* target = *L;  // 临时指针指向头结点
    int cur_pos = 0;    // 临时指针指向的结点位序，0即为头结点
    while(target != NULL && cur_pos < pos - 1){  
        target = target->next;
        cur_pos++;
    }
    // 2-插入新结点
    if(target == NULL)  // pos位置不合法
        return false;
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = target->next;
    target->next = s;
    return true;
#endif
    // 以上代码块可直接用两个基本操作来实现
    LNode* target = GetNodeByPos(*L, pos - 1); // 找到其前驱结点
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

bool ListDeleteByPos(LinkList* L, int pos, int* e){
    if(pos < 1)
        return false;
#if 0
    // 找到待删结点的前驱
    LNode* pre = *L;
    int cur_pos = 0;
    while (pre != NULL && cur_pos < pos - 1)
    {
        pre = pre->next;
        cur_pos++;
    }
#endif
    // 以上代码块可直接用以下基本操作来实现
    LNode* pre = GetNodeByPos(*L, pos - 1);
    if(pre == NULL) // 找不到第i个结点的前驱，说明i值不合法
        return false;
    if(pre->next == NULL) // 前驱结点已经是最后一个结点
        return false;
    
    // 记录待删结点的内容并返回
    LNode* p = pre->next;
    *e = p->data;
    pre->next = p->next;
    free(p);
    return true;
}

LNode* GetNodeByPos(LinkList L, int pos){
    if(pos < 0)  // pos为0时向下执行将返回头节点
        return NULL;
    LNode* target = L;
    int cur_pos = 0;
    while (cur_pos < pos && target != NULL)
    {
        target = target->next;
        cur_pos++;
    }
    return target;
}

LNode* GetNodeByValue(LinkList L, int value){
    LNode* target = L->next; // 从第一个结点开始找
    // 注意&&的短路，不能写成target->data != value && target != NULL
    while (target != NULL && target->data != value)
    {
        target = target->next;
    }
    return target;
}

int Length(LinkList L){
    int len = 0;
    LNode* tmp = L;
    // 如果没有头节点，就判断tmp是否为NULL
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        len++;
    }
    return len;
}

LinkList ListTailCreate(LinkList* L){
    int data = 0;
    *L = (LinkList)malloc(sizeof(LNode));  // 初始化空表
    (*L)->next = NULL;
    LNode* NewNode = NULL;
    LNode* r = *L;  // 尾指针初始化指向头节点
    puts("输入结点的值(输入9999时退出): ");
    scanf("%d", &data);
    while (data != 9999)
    {
        NewNode = (LNode*)malloc(sizeof(LNode));
        NewNode->data = data;
        r->next = NewNode;
        r = NewNode;  // 尾指针指向最后一个结点
        scanf("%d", &data);
    }
    r->next = NULL;
    return *L;
}

LinkList ListHeadCreate(LinkList* L){
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    int data = 0;
    puts("输入结点的值(输入9999时退出): ");
    scanf("%d", &data);
    while (data != 9999)
    {
        LNode* NewNode = (LNode*)malloc(sizeof(LNode));
        NewNode->data = data;
        NewNode->next = (*L)->next;
        (*L)->next = NewNode;
        scanf("%d", &data);
    }
    return *L;
}

LinkList ListReverse(LinkList* L){
    // 1-初始化一个新表
    LinkList ret = (LinkList)malloc(sizeof(LNode));
    ret->next = NULL;
    // 2-拷贝每一个结点并用头插的方式给新表
    LNode* tmp = (*L)->next;
    while (tmp != NULL)
    {
        LNode* NewNode = (LNode*)malloc(sizeof(LNode));
        NewNode->data = tmp->data;
        NewNode->next = ret->next;
        ret->next = NewNode;
        tmp = tmp->next;
    }
    // 3-旧表指向新表
    *L = ret;
}