#ifndef SQ_QUEUE_H
#define SQ_QUEUE_H

#include <stdbool.h>

/**
 * @brief 顺序队列的定义
 * @date  2024年2月27日21点41分
*/
#define MaxSize 10     // 队列中元素的最大个数
typedef struct {
    int data[MaxSize];
    int front;  // 队头指针
    int rear;   // 队尾指针，指向末尾元素的下一个位置
} SqQueue;

/**
 * @brief 顺序队列初始化
 * @date  2024年2月27日21点44分
*/
void InitSqQueue(SqQueue* SQ);

/**
 * @brief 顺序队列判空
 * @date  2024年2月27日21点44分
*/
bool IsEmpty(SqQueue SQ);

/**
 * @brief 入队
 * @date  2024年2月27日21点54分
*/
bool EnQueue(SqQueue* SQ, int e);

/**
 * @brief 出队
 * @date  2024年2月27日21点59分
*/
bool DeQueue(SqQueue* SQ, int* e);

/**
 * @brief 获取队头元素
 * @date  2024年2月27日22点06分
*/
bool GetHead(SqQueue SQ, int* e);

/**
 * @brief 获取当前元素个数
 * @date  2024年2月27日22点11分
*/
int GetElemNum(SqQueue SQ);

#endif // SQ_QUEUE_H