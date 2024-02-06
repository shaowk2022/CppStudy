#ifndef SQLISTS_H
#define SQLISTS_H

#define MaxLength 50

// 将顺序表的打印定义为宏，以实现重载
#define PRINT_LISTS(L) \
    {  \
        puts("the value of Lists: ");  \
        for(int i = 0; i < (L).length; i++){  \
            printf("%d\t", (L).data[i]);  \
        }  \
        puts("");  \
    }  \

/**
 * @brief 顺序表静态分配
 * @date  2024年2月6日01点03分
*/
typedef struct {
    int data[MaxLength];
    int length;
} StaticSqList;

/**
 * @brief 初始化静态顺序表，元素初值和长度均为0
 * @date 2024年2月6日01点01分
*/
void InitStaticSqList(StaticSqList* L);

/**
 * @brief 打印静态顺序表
 * @date  2024年2月6日01点22分
*/
void PrintStaticSqList(StaticSqList L);


/**
 * @brief 顺序表动态分配
 * @date  2024年2月6日01点13分
*/
typedef struct {
    int* data;
    int MaxSize;  // 最大容量
    int length;   // 当前容量
} SqList;

/**
 * @brief 初始化动态顺序表，分配内存空间
 * @date 2024年2月6日01点21分
*/
void InitSqList(SqList* L, int MaxSize);

/**
 * @brief 打印动态顺序表
 * @date  2024年2月6日01点23分
*/
void PrintSqLists(SqList L);


#endif // SQLISTS_H