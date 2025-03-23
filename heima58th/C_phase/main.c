#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

static char* strtoken(Token token) {
    switch (token.type) {
    // 井号
    case TOKEN_WELL:
        return "#";
    // 单字符Token
    case TOKEN_LEFT_PAREN:
        return "(";
    case TOKEN_RIGHT_PAREN:
        return ")";
    case TOKEN_LEFT_BRACKET:
        return "[";
    case TOKEN_RIGHT_BRACKET:
        return "]";
    case TOKEN_LEFT_BRACE:
        return "{";
    case TOKEN_RIGHT_BRACE:
        return "}";
    case TOKEN_COMMA:
        return ",";
    case TOKEN_DOT:
        return ".";
    case TOKEN_SEMICOLON:
        return ";";
    case TOKEN_TILDE:
        return "~";
    // 一个字符或两个字符的Token
    case TOKEN_PLUS:
        return "+";
    case TOKEN_PLUS_PLUS:
        return "++";
    case TOKEN_PLUS_EQUAL:
        return "+=";
    case TOKEN_MINUS:
        return "-";
    case TOKEN_MINUS_MINUS:
        return "--";
    case TOKEN_MINUS_EQUAL:
        return "-=";
    case TOKEN_MINUS_GREATER:
        return "->";
    case TOKEN_STAR:
        return "*";
    case TOKEN_STAR_EQUAL:
        return "*=";
    case TOKEN_SLASH:
        return "/";
    case TOKEN_SLASH_EQUAL:
        return "/=";
    case TOKEN_PERCENT:
        return "%";
    case TOKEN_PERCENT_EQUAL:
        return "%=";
    case TOKEN_AMPER:
        return "&";
    case TOKEN_AMPER_EQUAL:
        return "&=";
    case TOKEN_AMPER_AMPER:
        return "&&";
    case TOKEN_PIPE:
        return "|";
    case TOKEN_PIPE_EQUAL:
        return "|=";
    case TOKEN_PIPE_PIPE:
        return "||";
    case TOKEN_HAT:
        return "^";
    case TOKEN_HAT_EQUAL:
        return "^=";
    case TOKEN_EQUAL:
        return "=";
    case TOKEN_EQUAL_EQUAL:
        return "==";
    case TOKEN_BANG:
        return "!";
    case TOKEN_BANG_EQUAL:
        return "!=";
    case TOKEN_LESS:
        return "<";
    case TOKEN_LESS_EQUAL:
        return "<=";
    case TOKEN_LESS_LESS:
        return "<<";
    case TOKEN_GREATER:
        return ">";
    case TOKEN_GREATER_EQUAL:
        return ">=";
    case TOKEN_GREAER_GREATER:
        return ">>";
    // 字面值: 标识符, 字符, 字符串, 数字
    case TOKEN_IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN_CHARACTER:
        return "CHARACTER";
    case TOKEN_STRING:
        return "STRING";
    case TOKEN_NUMBER:
        return "NUMBER";
    // 关键字
    case TOKEN_SIGNED:
        return "SIGNED";
    case TOKEN_UNSIGNED:
        return "UNSIGNED";
    case TOKEN_CHAR:
        return "CHAR";
    case TOKEN_SHORT:
        return "SHORT";
    case TOKEN_INT:
        return "INT";
    case TOKEN_LONG:
        return "LONG";
    case TOKEN_FLOAT:
        return "FLOAT";
    case TOKEN_DOUBLE:
        return "DOUBLE";
    case TOKEN_STRUCT:
        return "STRUCT";
    case TOKEN_UNION:
        return "UNION";
    case TOKEN_ENUM:
        return "ENUM";
    case TOKEN_VOID:
        return "VOID";
    case TOKEN_IF:
        return "IF";
    case TOKEN_ELSE:
        return "ELSE";
    case TOKEN_SWITCH:
        return "SWITCH";
    case TOKEN_CASE:
        return "CASE";
    case TOKEN_DEFAULT:
        return "DEFAULT";
    case TOKEN_WHILE:
        return "WHILE";
    case TOKEN_DO:
        return "DO";
    case TOKEN_FOR:
        return "FOR";
    case TOKEN_BREAK:
        return "BREAK";
    case TOKEN_CONTINUE:
        return "CONTINUE";
    case TOKEN_RETURN:
        return "RETURN";
    case TOKEN_GOTO:
        return "GOTO";
    case TOKEN_CONST:
        return "CONST";
    case TOKEN_SIZEOF:
        return "SIZEOF";
    case TOKEN_TYPEDEF:
        return "TYPEDEF";
    // 辅助Token
    case TOKEN_ERROR:
        return "ERROR";
    case TOKEN_EOF:
        return "EOF";
    }
}

static void run(const char* source) {
    initScanner(source);
    int line = -1;
    for (;;) {
        Token token = scanToken();  // 每次扫出来一个Token
        if (token.line != line) {
            // 到达新的一行，打印当前行数
            printf("%4d", token.line);
            line = token.line;  // 更新line的值
        } else {                // 这一行还没处理完毕
            printf("   |");
        }
        // 输出当前Token的类型, token.length会传给*号以控制输出宽度
        printf("%12s 【%.*s】\n", strtoken(token), token.length, token.start);
        if (token.type == TOKEN_EOF)
            break;  // source的内容全部处理完毕
    }
}

// ToDo
static void repl() {
    // read evaluate print loop模式
    // 与用户交互，用户输入一行，分析一行，并输出结果
    char buffer[1024];
    printf("> ");
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        int len = strlen(buffer);
        if(len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
    }
    run(buffer);
}

static char* readFile(const char* path) {
    // 根据用户输入的文件名，读取文件内容为字符串，并在末尾添加\0
    FILE* stream = fopen(path, "r");
    if (!stream) {
        fprintf(stderr, "Open %s failed.\n", path);
        exit(1);
    }

    // 获取文件大小后将文件内容存在字符串中
    // 文件指针移动到末尾
    fseek(stream, 0, SEEK_END);
    long n = ftell(stream);                // 从开头到stream所在位置所包含的字节数
    char* content = (char*)malloc(n + 1);  // +1保存/0

    // 读取文件内容存入content
    rewind(stream);
    // 从stream开始读，每次读1个字节，共读取n次, bytes是读取成功的字节数
    int bytes = fread(content, 1, n, stream);
    content[bytes] = '\0';

    fclose(stream);
    return content;
}

static void runFile(const char* path) {
    // 处理该路径对应的.c文件
    char* source = readFile(path);
    run(source);
    free(source);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // 用户没有输入参数
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: scanner [path] \n");
        exit(1);
    }
    return 0;
}