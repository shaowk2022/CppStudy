#include <memory.h>
#include <stdbool.h>
#include <string.h>

#include "scanner.h"

// 定义Scanner对象
typedef struct Scanner {
    const char* start;    // Scanner当前扫描Token的起始位置
    const char* current;  // Scanner当前正在扫描的位置（字符）
    int line;             // Scanner当前扫描到的行数
} Scanner;

// 全局scanner对象
Scanner scanner;

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;  // 起始位置为源文件的首个字符
    scanner.line = 1;          // 起始行数为第一行
}

/***********************************************************
 *              scanToken()需要用的辅助方法                   *
 *     返回值使用static修饰，这样其它文件无法访问该函数         *
 ***********************************************************/
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// 返回是否为组成标识符的合法字符：字母或下划线
static bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

// 是否读取到字符串末尾
static bool isAtEnd() {
    return *scanner.current == '\0';
}

// 返回当前字符，并且current前进一步
static char advance() {
    char c = *scanner.current;
    scanner.current++;
    return c;
}

// 返回current所指字符,current不前进
static char peek() {
    return *scanner.current;
}

// 返回当前字符的下一个字符
static char peekNext() {
    if (isAtEnd())
        return '\0';  // current到末尾了，返回\0
    // current没到末尾，返回current指向字符的下一个字符
    return *(scanner.current + 1);
}

// 匹配当前字符是否是目标字符expected
static bool match(char expected) {
    if (isAtEnd())
        return false;  // 当前已经读取到末尾了
    if (peek() != expected)
        return false;  // 当前字符不是目标字符
    // 当前字符是目标字符，匹配成功，current前进一步
    scanner.current++;
    return true;
}

// 制作Token对象
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);  // 当前位置 - 起始位置 = token的长度
    token.line = scanner.line;
    return token;
}

// ToDo: 这里传的message是什么？
// 遇到非法情况时，如非法标识符@、$等，或字符（串）引号不能配对时，使用TokenError
static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = strlen(message);
    token.line = scanner.line;
    return token;
}

// 判断是否为空白字符
static bool isBlankChar(char c) {
    return c == ' ' || c == '\r' || c == '\t' || c == '\n';
}

// 判断是否为注释
static bool isNote() {
    return peek() == '/' && peekNext() == '/';
}

// 跳过空白字符和注释, 自己写的不知道对不对【对】
static void skipWhiteSpace() {
    // 不是空白字符且不是注释，则循环结束
    while (isBlankChar(peek()) || isNote()) {
        if (isBlankChar(peek())) {  // 遇到空白字符
            if (peek() == '\n')
                scanner.line++;
            advance();
        } else  // 遇到注释则跳过这一行
        {
            // current一直走直到遇到\n, 说明current到达行尾
            while (peek() != '\n')
                advance();
            advance();       // current走到下一行的开头
            scanner.line++;  // 行数+1
        }
    }
    // 最后current会指向第一个有效字符，更新start
    scanner.start = scanner.current;
}

// 检测是否为关键字type
/**
 * @param start: 起始索引
 * @param length: 比较长度
 * @param rest: 要比较的字符串
 * @param type: 如果匹配则是type类型的关键字
 */
static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    // 获取当前Token的长度
    int len = (int)(scanner.current - scanner.start);
    // Token长度和关键字长度相等且内容相等
    if (start + length == len && memcmp(scanner.start + start, rest, length) == 0)
        return type;
    return TOKEN_IDENTIFIER;  // 不是关键字则当前Token是一个标识符
}

// 判断当前Token到底是标识符还是关键字
static TokenType identifierType() {
    // 将所有关键字放入Trie树，查表确认
    char c = scanner.start[0];  // 拿到第一个字符
    // 用switch实现Trie树
    switch (c) {
    case 'b':
        return checkKeyword(1, 4, "reak", TOKEN_BREAK);
    case 'c': {
        c = scanner.start[1];
        switch (c) {
        case 'a':
            return checkKeyword(2, 2, "se", TOKEN_CASE);
        case 'h':
            return checkKeyword(2, 2, "ar", TOKEN_CHAR);
        case 'o': {
            c = scanner.start[3];
            switch (c) {
            case 't':
                return checkKeyword(4, 4, "inue", TOKEN_CONTINUE);
            case 's':
                return checkKeyword(4, 1, "t", TOKEN_CONST);
            }
        }
        }
    }
    case 'd': {
        c = scanner.start[1];
        switch (c) {
        case 'e':
            return checkKeyword(2, 5, "fault", TOKEN_DEFAULT);
        case 'o':
            return checkKeyword(2, 4, "uble", TOKEN_DOUBLE);
        }
    }
    case 'e': {
        c = scanner.start[1];
        switch (c) {
        case 'n':
            return checkKeyword(2, 2, "um", TOKEN_CASE);
        case 'l':
            return checkKeyword(2, 2, "se", TOKEN_ELSE);
        }
    }
    case 'f': {
        c = scanner.start[1];
        switch (c) {
        case 'l':
            return checkKeyword(2, 3, "oat", TOKEN_FLOAT);
        case 'o':
            return checkKeyword(2, 1, "r", TOKEN_FOR);
        }
    }
    case 'g':
        return checkKeyword(1, 3, "oto", TOKEN_GOTO);
    case 'i': {  // Todo: 这里的判断不确定写的对不对
        c = scanner.start[1];
        switch (c) {
        case 'n':
            return checkKeyword(2, 1, "t", TOKEN_INT);
        default:
            return checkKeyword(1, 1, "f", TOKEN_IF);
        }
    }
    case 'l':
        return checkKeyword(1, 3, "ong", TOKEN_LONG);
    case 'r':
        return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's': {
        c = scanner.start[1];
        switch (c) {
        case 'h':
            return checkKeyword(2, 3, "ort", TOKEN_SHORT);
        case 'i': {
            c = scanner.start[2];
            switch (c) {
            case 'g':
                return checkKeyword(3, 3, "ned", TOKEN_SIGNED);
            case 'z':
                return checkKeyword(3, 3, "eof", TOKEN_SIZEOF);
            }
        }
        case 't':
            return checkKeyword(2, 4, "ruct", TOKEN_STRUCT);
        case 'w':
            return checkKeyword(2, 4, "itch", TOKEN_SWITCH);
        }
    }
    case 't':
        return checkKeyword(1, 6, "ypedef", TOKEN_TYPEDEF);
    case 'u': {
        c = scanner.start[2];
        switch (c) {
        case 's':
            return checkKeyword(3, 5, "igned", TOKEN_UNSIGNED);
        case 'i':
            return checkKeyword(3, 2, "on", TOKEN_UNION);
        }
    }
    case 'v':
        return checkKeyword(1, 3, "oid", TOKEN_VOID);
    case 'w':
        return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }
    // Trie树中均不匹配，说明不是关键字而是标识符
    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    // identifier只能包含数字字母下划线
    while (isAlpha(peek()) || isDigit(peek()))
        advance();  // current前进一步
    // 现在current指向的不是字母数字下划线
    // 确定中间这一段组成的Token到底是关键字还是标识符
    // identifierType()会返回关键字的类型或者标识符
    return makeToken(identifierType());
}

// ToDo 判断是否为数字并返回相应的Token
static Token number() {
    // start指向第一个数字，current指向start下一位置
    bool hasNumberBeforeDot = true;
    bool hasNumberAfterDot = false;
    bool foundDot = false;
    while (!isAtEnd()) {
        char c = peek();  // current指向字符
        if (c == '.') {
            if (!foundDot) {
                foundDot = true;
                advance();  // 这个点合法，继续向后处理
            } else
                return makeToken(TOKEN_ERROR);  // 遇到两次点
        } else if (isDigit(c)) {
            if (foundDot)
                hasNumberAfterDot = true;  // 小数点后有数字
            advance();                     // 继续向后处理
        } else {                           // 遇到其他字符
            if (foundDot && !hasNumberAfterDot)
                return makeToken(TOKEN_ERROR);  // 小数点后无数字
            break;
        }
    }
    // 解析出了一个有效数字
    return makeToken(TOKEN_NUMBER);
}

static Token string() {
    // 进入这里说明start位置已经是"了，且current指向下一位置
    while (!isAtEnd()) {
        char c = advance();
        if (c == '"')
            return makeToken(TOKEN_STRING);  // 是正确的字符串
    }
    return makeToken(TOKEN_ERROR);  // 字符串缺少右引号
}

static Token character() {
    // 当前start指向左引号，current指向下一位置
    advance();  // current前进一步
    char c = advance();
    return c == '\'' ? makeToken(TOKEN_CHARACTER) : makeToken(TOKEN_ERROR);
}

/***********************************************************
 *                        分词                             *
 ***********************************************************/

Token scanToken() {
    // 跳过空白字符和注释
    skipWhiteSpace();
    // 记录下一个Token的起始位置
    scanner.start = scanner.current;
    if (isAtEnd())
        return makeToken(TOKEN_EOF);

    char c = advance();
    if (isAlpha(c))
        return identifier();  // 字母或下划线开头，判断是标识符还是关键字
    if (isDigit(c))
        return number();  // 数字开头，判断是否为数字Token

    // 以符号开头
    switch (c) {
    case '#':
        return makeToken(TOKEN_WELL);
    // 单字符Token
    case '(':
        return makeToken(TOKEN_LEFT_PAREN);
    case ')':
        return makeToken(TOKEN_RIGHT_PAREN);
    case '[':
        return makeToken(TOKEN_LEFT_BRACKET);
    case ']':
        return makeToken(TOKEN_RIGHT_BRACKET);
    case '{':
        return makeToken(TOKEN_LEFT_BRACE);
    case '}':
        return makeToken(TOKEN_RIGHT_BRACE);
    case ',':
        return makeToken(TOKEN_COMMA);
    case '.':
        return makeToken(TOKEN_DOT);
    case ';':
        return makeToken(TOKEN_SEMICOLON);

    // 单或双字符Token
    case '+':
        if (match('+'))
            return makeToken(TOKEN_PLUS_PLUS);
        else if (match('='))
            return makeToken(TOKEN_PLUS_EQUAL);
        else
            return makeToken(TOKEN_PLUS);
    case '-':
        if (match('-'))
            return makeToken(TOKEN_MINUS_MINUS);
        else if (match('='))
            return makeToken(TOKEN_MINUS_EQUAL);
        else if (match('>'))
            return makeToken(TOKEN_MINUS_GREATER);
        else
            return makeToken(TOKEN_MINUS);
    case '*':
        if (match('='))
            return makeToken(TOKEN_STAR_EQUAL);
        else
            return makeToken(TOKEN_STAR);
    case '/':
        if (match('='))
            return makeToken(TOKEN_SLASH_EQUAL);
        else
            return makeToken(TOKEN_SLASH);
    case '%':
        if (match('='))
            return makeToken(TOKEN_PERCENT_EQUAL);
        else
            return makeToken(TOKEN_PERCENT);
    case '&':
        if (match('&'))
            return makeToken(TOKEN_AMPER_AMPER);
        else if (match('='))
            return makeToken(TOKEN_AMPER_EQUAL);
        else
            return makeToken(TOKEN_AMPER);
    case '|':
        if (match('|'))
            return makeToken(TOKEN_PIPE_PIPE);
        else if (match('='))
            return makeToken(TOKEN_PIPE_EQUAL);
        else
            return makeToken(TOKEN_PIPE);
    case '^':
        if (match('='))
            return makeToken(TOKEN_HAT_EQUAL);
        else
            return makeToken(TOKEN_HAT);
    case '=':
        if (match('='))
            return makeToken(TOKEN_EQUAL_EQUAL);
        else
            return makeToken(TOKEN_EQUAL);
    case '!':
        if (match('='))
            return makeToken(TOKEN_BANG_EQUAL);
        else
            return makeToken(TOKEN_BANG);
    case '<':
        if (match('<'))
            return makeToken(TOKEN_LESS_LESS);
        else if (match('='))
            return makeToken(TOKEN_LESS_EQUAL);
        else
            return makeToken(TOKEN_LESS);
    case '>':
        if (match('>'))
            return makeToken(TOKEN_GREAER_GREATER);
        else if (match('='))
            return makeToken(TOKEN_GREATER_EQUAL);
        else
            return makeToken(TOKEN_GREATER);

    // 字符(串)Token
    case '"':
        return string();
    case '\'':
        return character();
    }

    return errorToken("Unexpected character.");
}
