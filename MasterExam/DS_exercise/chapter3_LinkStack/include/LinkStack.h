#ifndef LINK_STACK_H
#define LINK_STACK_H

#include <stdbool.h>

/**
 * @brief 链栈的定义
 * @date  2024年2月26日22点23分
*/
struct LinkNode
{
    int data;
    struct LinkNode* next;  // 首结点的next作为栈顶指针
};
typedef struct LinkNode LinkNode;
typedef struct LinkNode* LinkStack;

/**
 * @brief 链栈初始化
 * @date  2024年2月26日22点25分
*/
bool InitLinkStack(LinkStack* LS);

/**
 * @brief 链栈判空
 * @date  2024年2月26日22点32分
*/
bool isEmpty(LinkStack LS);

/**
 * @brief 入栈
 * @date  2024年2月26日22点35分
*/
bool Push(LinkStack* LS, int e);

/**
 * @brief 出栈
 * @date  2024年2月26日22点35分
*/
bool Pop(LinkStack* LS, int* e);

/**
 * @brief 读取栈顶元素
 * @date  2024年2月26日23点32分
*/
bool GetTop(LinkStack LS, int* e);

/**
 * @brief 销毁链栈
 * @date  2024年2月26日23点45分
*/
const char* Destroy(LinkStack* LS);

#endif // LINK_STACK_H