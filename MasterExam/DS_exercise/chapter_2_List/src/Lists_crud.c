#include <stdlib.h>
#include <stdio.h>

#include "Lists.h"
LNode* create_ListHeader(int e){
    LNode* head = (LNode*)malloc(sizeof(LNode));
    head->data = e;
    head->next = NULL;
    return head;
}

/*注意这里的头指针要用二级指针来传递，以使形参改变实参*/
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