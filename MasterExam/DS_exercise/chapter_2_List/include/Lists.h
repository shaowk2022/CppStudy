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

LNode* create_ListHeader(int e);

/*注意这里的头指针要用二级指针来传递，以使形参改变实参*/
RETCODE insert_from_head(LNode** head, int e);

RETCODE insert_from_tail(LNode* head, int e);
void traverse_Lists(LNode* head);

#endif  // _LISTS_H_