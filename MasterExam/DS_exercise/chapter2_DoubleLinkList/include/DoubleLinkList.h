#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#include <stdbool.h>

struct DNode{
    int data;
    struct DNode* prior;
    struct DNode* next;
};

typedef struct DNode DNode;
typedef struct DNode* DLinkList;

/**
 * @brief 初始化双链表
 * @date  2024年2月19日23点03分
*/
bool InitDLinkList(DLinkList* L);

/**
 * @brief 双链表判空(带头节点)
 * @date  2024年2月19日23点08分
*/
bool IsEmpty(DLinkList L);

/**
 * @brief 双链表后插操作
 * @date  2024年2月19日23点13分
*/
bool InsertNextDNode(DNode* p, int e);

/**
 * @brief 元素打印
 * @date  2024年2月19日23点19分
*/
void PrintElem(DLinkList L);

/**
 * @brief 删除后继结点
 * @date  2024年2月19日23点28分
*/
bool DeleteNextDNode(DNode* p);

/**
 * @brief 销毁链表
 * @date  2024年2月19日23点33分
*/
void DestroyDLinkList(DLinkList* L);

/**
 * @brief 从指定结点开始遍历
 * @date  2024年2月19日23点38分
*/
void DLinkListTraverse(DNode* p);
// ToDo: 按位序插入，指定结点前插

#endif  // DOUBLELINKLIST_H