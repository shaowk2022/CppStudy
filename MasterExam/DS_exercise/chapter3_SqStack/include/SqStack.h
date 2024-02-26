#ifndef SQ_STACK_H
#define SQ_STACK_H

#include <stdbool.h>

/**
 * @brief 顺序栈定义
 * @date  2024年2月26日21点39分
*/
#define MaxSize 5
typedef struct {
    int data[MaxSize];
    int top;  // 栈顶指针
} SqStack;

/**
 * @brief 顺序栈初始化
 * @date  2024年2月26日21点42分
*/
void InitSqStack(SqStack* SS);

/**
 * @brief 顺序栈判空
 * @date  2024年2月26日21点43分
*/
bool isEmpty(SqStack SS);

/**
 * @brief 顺序栈判满
 * @date  2024年2月26日22点15分
*/
bool isFull(SqStack SS);

/**
 * @brief 入栈操作
 * @date  2024年2月26日21点47分
*/
bool Push(SqStack* SS, int e);

/**
 * @brief 出栈操作
 * @date  2024年2月26日21点51分
*/
bool Pop(SqStack* SS, int* e);

/**
 * @brief 读取栈顶元素
 * @date  2024年2月26日22点00分
*/
bool GetTop(SqStack SS, int* e);

/**
 * @brief 销毁顺序栈
 * @date  2024年2月26日22点03分
*/
bool DestroyStack(SqStack* SS);


#endif  // SQ_STACK_H