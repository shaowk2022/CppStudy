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

    int ret = -1;
    ListDeleteByPos(&L, 3, &ret); // 删除5
    printf("%d\n", ret);
    ListDeleteByPos(&L, 2, &ret); // 删除30
    printf("%d\n", ret);
    ListDeleteByPos(&L, 1, &ret); // 删除10
    printf("%d\n", ret);
    ListPrintElem(L);

    printf("链表：%s \n", IsEmpty(L) ? "NULL" : "Not NULL");
    LNode* tmp = GetNodeByValue(L, 10);
    printf("值为10的结点: %s\n", tmp == NULL ? "不存在" : "存在");
}

void main(){
    run_Lists_app();
}