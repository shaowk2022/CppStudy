#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;
typedef struct 
{
    Node* front;
    Node* rear;
    int length;
} LinkQueue;

/**
 * @brief 初始化链队列(带头结点)
 * @date  2024年2月27日22点30分
*/
void InitLinkQueue(LinkQueue* LQ);

/**
 * @brief 链队列判空(带头结点)
 * @date  2024年2月27日22点39分
*/
bool IsEmpty(LinkQueue LQ);

/**
 * @brief 入队(带头结点)
 * @date  2024年2月27日22点44分
 * @note  链式存储，不存在队满的情况
*/
bool EnQueue(LinkQueue* LQ, int e);

/**
 * @brief 出队(带头结点)
 * @date  2024年2月27日23点07分
*/
bool DeQueue(LinkQueue* LQ, int* e);

/**
 * @brief 获取当前长度
 * @date  2024年2月27日23点18分
*/
int GetLength(LinkQueue LQ);

/**
 * @brief 销毁链队列
 * @date  2024年2月27日23点28分
*/
void Destroy(LinkQueue* LQ);

#endif  // LINK_QUEUE_H