#include <stdio.h>

#include "Lists.h"

void main(){
    RETCODE retCode = OK;
    LNode* head = create_ListHeader(1);
    if(NULL == head){
        perror("create Lists failed.");
        return;
    }
    printf("ListHeader Address: %p \n", head);

    retCode = insert_from_head(&head, 10);
    retCode = insert_from_head(&head, 20);
    retCode = insert_from_head(&head, 30);
    if(retCode == ERROR){
        puts("insert failed.");
    }

    traverse_Lists(head);

}