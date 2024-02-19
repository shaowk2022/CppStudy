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
bool ListInsertByPos(LinkList* L, int pos, int e);

/**
 * @brief 指定结点后插操作
 * @date  2024年2月19日10点42分
*/
bool ListInsertNextNode(LNode* p, int e);

/**
 * @brief 指定结点前插操作
 * @date  2024年2月19日11点20分
*/
bool ListInsertPriorNode(LNode* p, int e);

/**
 * @brief 打印链表元素
 * @date  2024年2月19日10点48分
*/
void ListPrintElem(LinkList L);

/**
 * @brief 按位序删除
 * @date  2024年2月19日14点38分
 * @note  被删除元素用e返回
*/
bool ListDeleteByPos(LinkList* L, int pos, int* e);

/**
 * @brief 按位查找结点
 * @date  2024年2月19日16点25分
*/
LNode* GetNodeByPos(LinkList L, int pos);

/**
 * @brief 按值查找结点
 * @date  2024年2月19日16点26分
*/
LNode* GetNodeByValue(LinkList L, int value);

#endif  // LISTS_H