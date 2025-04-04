/**
 * 作业：实现一个Linux的wc命令，即WordCount, 统计字符个数、单词个数、换行个数, 使用个数为wc <文件名>
 * 解析：难点在于记录单词个数，使用有限状态机
 * @date 2025年2月12日21点56分
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum State {
    OUTSIDE,  // 不在单词内
    INSIDE    // 在单词内
} State;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: wc <fileName>.\n");
        exit(-1);
    }
    FILE* stream = fopen(argv[1], "r");  // 读取文件
    if (stream == NULL) {
        fprintf(stderr, "file not exists.\n");
        exit(-1);
    }
    int characters = 0, words = 0, lines = 0;
    State state = OUTSIDE;  // 初始状态为单词外
    char c;
    while ((c = fgetc(stream)) != EOF) {
        characters++;
        if (c == '\n')
            lines++;
        if (isblank(c)) {  // c是空白字符，当前状态在单词外
            state = OUTSIDE;
        } else {
            if (state == OUTSIDE)
                words++;     // 非空白字符且上一次的状态是在单词外，则记录一个单词
            state = INSIDE;  // 状态从OUTSIDE->INSIDE
        }
    }
    printf("characters: %8d, \twords: %8d, \tlines: %8d \n", characters, words, lines);
    // 关闭文件
    fclose(stream);
    return 0;
}