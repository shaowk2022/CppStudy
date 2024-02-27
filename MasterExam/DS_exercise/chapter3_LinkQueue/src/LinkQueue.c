#include <stdio.h>
#include "LinkQueue.h"

void InitLinkQueue(LinkQueue* LQ){
    LQ->front = LQ->rear = (Node*)malloc(sizeof(Node));
    LQ->front->next = NULL;
    LQ->length = 0;
    // 若是不带头节点的，则使用如下初始化方式
    // LQ->front = NULL;
    // LQ->rear = NULL;
}

bool IsEmpty(LinkQueue LQ){
    return LQ.front == LQ.rear;
    // 若是不带头节点的，则使用如下判空方式
    // return LQ.front == NULL;
}

bool EnQueue(LinkQueue* LQ, int e){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = NULL;
    LQ->rear->next = newNode;  // 新结点插入到队尾后
    LQ->rear = newNode;  // 队尾指针指向新结点

    // 如果不带头节点，要单独处理插入首个结点的逻辑，将上面22、23两行改为如下操作
    // if(LQ->front == NULL){
    //     // 队空，当前插入的结点为首结点
    //     LQ->front = newNode;
    //     LQ->rear = newNode;
    // } else {
    //     LQ->rear->next = newNode;
    //     LQ->rear = newNode;
    // }
    LQ->length++;
    return true;
}

bool DeQueue(LinkQueue* LQ, int* e){
    if(LQ->front == LQ->rear)
        return false;  // 队空
    Node* target = LQ->front->next;  // 指向待出队结点
    *e = target->data;
    LQ->front->next = target->next;  // 修改头节点的next指向
    if(LQ->rear == target){
        // 若出队的刚好是末尾元素，需修改队尾指针
        LQ->rear = LQ->front;
    }

    // 如果是不带头节点，则使用如下操作
    // if(LQ->front == NULL)
    //     return false;  // 队空
    // Node* target = LQ->front;  // 指向待出队结点
    // *e = target->data;
    // LQ->front = target->next;
    // if(LQ->rear == target){
    //      // 若出队的刚好是末尾元素, 队头/尾指针还原到初始状态
    //      LQ->front = NULL;
    //      LQ->rear = NULL;
    // }
    LQ->length--;
    free(target);
    return true;
}

int GetLength(LinkQueue LQ){
    return LQ.length;
}

void Destroy(LinkQueue* LQ){
    // 带头结点链队列销毁
    while (LQ->front->next != NULL)
    {
        Node* target = LQ->front->next;
        LQ->front->next = target->next;
        free(target);
        LQ->length--;
    }
    free(LQ->front);
    LQ->front = NULL;
    LQ->rear = NULL;
    puts("销毁成功");
}