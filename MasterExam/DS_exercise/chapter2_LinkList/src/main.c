#include <stdio.h>

#include "LinkLists.h"

void run_Lists_app(){
    LinkList L;
    InitList(&L);
    ListInsertByPos(&L, 1, 1);
    ListInsertByPos(&L, 2, 2);
    ListInsertByPos(&L, 3, 3);

    ListInsertNextNode(L, 5);
    ListInsertNextNode(L, 10);
    ListInsertPriorNode(L->next->next, 30);
    
    ListPrintElem(L);
    printf("链表：%s \n", IsEmpty(L) ? "NULL" : "Not NULL");
}

void main(){
    run_Lists_app();
}