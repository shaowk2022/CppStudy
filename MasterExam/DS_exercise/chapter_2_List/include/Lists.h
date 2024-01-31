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
RETCODE insert_from_head(LNode** head, int e);
void traverse_Lists(LNode* head);

#endif  // _LISTS_H_