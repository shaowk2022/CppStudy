#ifndef _LISTS_H_
#define _LISTS_H_

#define MAX_SIZE 100

typedef struct LNode
{
    int data;
    struct LNode* next;
} LNode;

typedef enum RETCODE {
    ERROR,
    OK
} RETCODE;

/**
 * @brief 创建链表头结点
*/
LNode* create_ListHeader(int e);

/**
 * @brief 创建定长链表
*/
RETCODE create_Lists(LNode** head, int length);

/**
 * @brief 头插法
 * @note 注意这里的头指针要用二级指针来传递，以使形参改变实参
*/
RETCODE insert_from_head(LNode** head, int e);

/**
 * @brief 尾插法
*/
RETCODE insert_from_tail(LNode* head, int e);

/**
 * @brief 遍历链表元素
*/
void traverse_Lists(LNode* head);

#endif  // _LISTS_H_