#include <stdbool.h>
#include "SqStack.h"

void InitSqStack(SqStack* SS){
    SS->top = -1;
}

bool isEmpty(SqStack SS){
    return SS.top == -1;
}

bool Push(SqStack* SS, int e){
    if (SS->top == MaxSize - 1)
        return false;  // 栈满
    SS->top++;  // 栈顶指针+1
    SS->data[SS->top] = e;  // 新元素入栈
    return true;
}

bool Pop(SqStack* SS, int* e){
    if(SS->top == -1)
        return false; // 栈空
    *e = SS->data[SS->top]; // 元素出栈
    SS->top--; // 栈顶指针-1
    return true;
}

bool GetTop(SqStack SS, int* e){
    if(SS.top == -1)
        return false; // 栈空
    *e = SS.data[SS.top];
    return true;
}

bool DestroyStack(SqStack* SS){
    SS->top = -1; // 逻辑上删除
    // 因为是用数组申请的空间，所以会被系统自动回收，无需使用free()
    return true;
}

bool isFull(SqStack SS){
    if(SS.top == MaxSize - 1)
        return true;
    return false;
}