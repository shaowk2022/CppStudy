#include <stdio.h>

#include "Lists.h"

void main(){
    int length = 0;  // 长度
    RETCODE retCode = OK;
    LNode* head = create_ListHeader(0);
    if(NULL == head){
        perror("create Lists failed.");
        return;
    }
    // printf("ListHeader Address: %p \n", head);
    puts("输入节点个数: ");
    scanf("%d", &length);
    retCode = create_Lists(&head, length);
    if(retCode == ERROR){
        puts("create failed.");
    }
    traverse_Lists(head);

}