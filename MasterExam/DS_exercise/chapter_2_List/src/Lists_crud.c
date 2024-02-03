#include <stdlib.h>
#include <stdio.h>

#include "Lists.h"

LNode* create_ListHeader(int e){
    LNode* head = (LNode*)malloc(sizeof(LNode));
    head->data = e;
    head->next = NULL;
    return head;
}

RETCODE create_Lists(LNode** head, int length){
    int flag = 0;  // 1-头插法，2-尾插法，0-结束
    if(length <= 0)
        return ERROR;
    puts("1-头插法, 2-尾插法: ");
    scanf("%d", &flag);
    if(flag != 1 && flag != 2)
        return ERROR;
    puts("输入节点元素值：");
    int e = 0;
    for(int i = 0; i < length; i++){
        scanf("%d", &e);
        flag == 1 ? insert_from_head(head, e) : insert_from_tail(*head, e);    
    }
    return OK;
}

RETCODE insert_from_head(LNode** head, int e){
    if (head == NULL)
    {
        perror("Head is NULL. Insert failed.");
        return ERROR;
    }
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = e;
    newNode->next = *head;
    *head = newNode;
    return OK;
}

RETCODE insert_from_tail(LNode* head, int e){
    if(head == NULL){
        perror("Head is NULL. Insert failed.");
        return ERROR;
    }
    // 找到链表尾
    LNode* tail = head;
    while (tail->next)
    {
        tail = tail->next;
    }
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = e;
    newNode->next = NULL;
    tail->next = newNode;
    return OK;
}

void traverse_Lists(LNode* head){
    LNode* temp = head;
    puts("Value: ");
    while (temp)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    puts("");
}