#include <stdio.h>

#include "LinkQueue.h"

void run_LinkQueue_app(){
    LinkQueue LQ;
    InitLinkQueue(&LQ);
    printf("NULL? %d , Length: %d \n", IsEmpty(LQ), GetLength(LQ));

    EnQueue(&LQ, 1);
    EnQueue(&LQ, 2);
    EnQueue(&LQ, 3);
    printf("NULL? %d , Length: %d \n", IsEmpty(LQ), GetLength(LQ));

    int ret = 0;
    DeQueue(&LQ, &ret);
    printf("ret: %d\n", ret);   // 1
    DeQueue(&LQ, &ret);
    printf("ret: %d\n", ret);   // 2
    printf("NULL? %d , Length: %d \n", IsEmpty(LQ), GetLength(LQ));

    Destroy(&LQ);
    printf("Destroy之后的length: %d\n", LQ.length);
    printf("%d \n", DeQueue(&LQ, &ret));  // 因为已销毁，所以返回false, 输出为0
    printf("ret: %d\n", ret);   // 3
}

int main(){
    run_LinkQueue_app();
    return 0;
}