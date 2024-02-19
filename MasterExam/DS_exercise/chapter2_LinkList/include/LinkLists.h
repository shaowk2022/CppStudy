#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 100

#define LOG(msg) puts(msg)

struct LNode
{
    int data;
    struct LNode* next;
};

typedef struct LNode LNode;
typedef struct LNode* LinkList;

/**
 * @brief 带头结点单链表初始化
 * @date  2024年2月6日15点35分
*/ 
bool InitList(LinkList* L);

/**
 * @brief 带头结点单链表判空
 * @date  2024年2月6日15点38分
*/
bool IsEmpty(LinkList L);

/**
 * @brief 按位序插入
 * @date  2024年2月18日11点13分
*/
bool ListInsert(LinkList* L, int pos, int e);

#endif  // LISTS_H