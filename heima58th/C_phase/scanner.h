// scanner.h 防止重复包含
#ifndef scanner_h
#define scanner_h

// 枚举Token的类型
typedef enum TokenType{
    // 处理#号
    TOKEN_WELL,
    // 单字符Token
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,		// '(', ')'
    TOKEN_LEFT_BRACKET, TOKEN_RIGHT_BRACKET,	// '[', ']'
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,  		// '{', '}'
    TOKEN_COMMA, TOKEN_DOT, TOKEN_SEMICOLON,	// ',', '.', ';'
    TOKEN_TILDE,  // '~'
    // 1或2字符Token
    TOKEN_PLUS, TOKEN_PLUS_PLUS, TOKEN_PLUS_EQUAL, // '+', '++', '+='
    // '-', '--', '-=', '->'
    TOKEN_MINUS, TOKEN_MINUS_MINUS, TOKEN_MINUS_EQUAL, TOKEN_MINUS_GREATER,
    TOKEN_STAR, TOKEN_STAR_EQUAL,			// '*', '*='
    TOKEN_SLASH, TOKEN_SLASH_EQUAL, 		// '/', '/=', 
    TOKEN_PERCENT, TOKEN_PERCENT_EQUAL, 	// '%', '%='
    TOKEN_AMPER, TOKEN_AMPER_EQUAL, TOKEN_AMPER_AMPER, 	// '&', '&=', '&&'
    TOKEN_PIPE, TOKEN_PIPE_EQUAL, TOKEN_PIPE_PIPE,		// '|', '|=', '||'
    TOKEN_HAT, TOKEN_HAT_EQUAL, 		// '^', '^='
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL, 	// '=', '=='
    TOKEN_BANG, TOKEN_BANG_EQUAL,	  	// '!', '!='
    TOKEN_LESS, TOKEN_LESS_EQUAL, TOKEN_LESS_LESS, 				// '<', '<=', '<<'
    TOKEN_GREATER, TOKEN_GREATER_EQUAL, TOKEN_GREAER_GREATER, 	// '>', '>=', '>>'
                                                                // 附加题：'>>=', '<<='
    // 字面值: 标识符, 字符, 字符串, 数字
    TOKEN_IDENTIFIER, TOKEN_CHARACTER, TOKEN_STRING, TOKEN_NUMBER,
    // 关键字
    TOKEN_SIGNED, TOKEN_UNSIGNED,
    TOKEN_CHAR, TOKEN_SHORT, TOKEN_INT, TOKEN_LONG,
    TOKEN_FLOAT, TOKEN_DOUBLE,
    TOKEN_STRUCT, TOKEN_UNION, TOKEN_ENUM, TOKEN_VOID,
    TOKEN_IF, TOKEN_ELSE, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT,
    TOKEN_WHILE, TOKEN_DO, TOKEN_FOR,
    TOKEN_BREAK, TOKEN_CONTINUE, TOKEN_RETURN, TOKEN_GOTO,
    TOKEN_CONST, TOKEN_SIZEOF, TOKEN_TYPEDEF,
    // 辅助Token：错误Token和读取结束符
    TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct Token{
    TokenType type;  // Token的类型
    const char* start;  // Token的起始位置
    int length;  // Token的长度
    int line;  // Token所在行数
} Token;

// 操作定义
/**
 * @brief 初始化scanner
 * @param source为原文件的全部内容，按字符串形式读取
 */
void initScanner(const char* source);

/**
 * @brief 开始扫描文件中的Token
 * @return 下一个Token对象
 */
Token scanToken();

#endif // scanner.h