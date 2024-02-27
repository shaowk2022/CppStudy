#include "SqQueue.h"

void InitSqQueue(SqQueue* SQ){
    SQ->front = 0;
    SQ->rear = 0;
}
bool IsEmpty(SqQueue SQ){
    return SQ.front == SQ.rear;
}

bool EnQueue(SqQueue* SQ, int e){
    // 判断队满，这样写因为牺牲掉末尾最后一个位置，队尾指针若+1将会与队头指针重合
    if((SQ->rear + 1) % MaxSize == SQ->front)
        return false; 
    SQ->data[SQ->rear] = e;  // 元素入队
    SQ->rear = (SQ->rear + 1) % MaxSize; // 队尾指针+1再取余，构成逻辑上的循环队列
    return true;
}

bool DeQueue(SqQueue* SQ, int* e){
    // 判断队空
    if(SQ->front == SQ->rear)
        return false;
    *e = SQ->data[SQ->front];
    SQ->front = (SQ->front + 1) % MaxSize; // 队头指针+1再取余，构成逻辑上的循环队列
    return true;
}

bool GetHead(SqQueue SQ, int* e){
    if(SQ.front == SQ.rear)
        return false;  // 队空
    *e = SQ.data[SQ.front];
    return true;
}

int GetElemNum(SqQueue SQ){
    return (SQ.front + MaxSize - SQ.rear) % MaxSize;
}