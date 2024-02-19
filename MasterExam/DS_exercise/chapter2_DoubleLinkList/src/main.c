#include <stdio.h>
#include "DoubleLinkList.h"

void main(){
    DLinkList L;
    InitDLinkList(&L);
    InsertNextDNode(L, 1);
    InsertNextDNode(L, 2);
    InsertNextDNode(L, 3);
    PrintElem(L);
    
}