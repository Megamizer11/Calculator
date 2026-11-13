#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define APPEND_TOKEN(token_type) \
                Token newToken = {token_type, lastPos+1, substr(code, lastPos, i)};\
                (*outputTokens)[tokensCount] = newToken;\
                tokensCount++;\
                lastPos = i;

enum TokenType {
    NUMBER,
    OPPAR,
    CLPAR,
    PLUS,
    MINUS,
    MULT,
    DIVIDE,
    _TOKENTYPES_COUNT
};
const char* _TokenTypes[] = {"NUMBER", "OPPAR", "CLPAR", "PLUS", "MINUS", "MULT", "DIVIDE"};

typedef struct {
    int type;
} TokenType;

typedef struct {
    TokenType tokenType;
    int pos;
    const char* literal;
} Token;

char* substr(const char* str, int start, int end) {  // (start, end]
    if (!str) {
        printf("substr str is NULL\n");
        exit(EXIT_FAILURE);
    } 
    int str_len = strlen(str);
    if (start < -1 || start > end || end >= str_len) {
        printf("substr index overflow, start=%d, end=%d\n", start, end);
        exit(EXIT_FAILURE);
    }
    int substr_len = end - start;
    char* sub = (char *)malloc((substr_len + 1) * sizeof(char));
    if (!sub) {
        printf("substr malloc failure\n");
        exit(EXIT_FAILURE);
    }
    memcpy(sub, str + start + 1, substr_len);  // + 1, так как start не включительно
    sub[substr_len] = '\0';
    return sub;
}

void print(Token token) {
    printf("Token: \"%s\", type=%s, pos=%d\n", token.literal, _TokenTypes[token.tokenType.type], token.pos);
}

int lexAnalysis(const char* code, Token *outputTokens[]) {
    if (_TOKENTYPES_COUNT != sizeof(_TokenTypes) / sizeof(_TokenTypes[0])) {
        printf("TokenType enum and TokenTypes array must have same size");
        exit(EXIT_FAILURE);
    }

    int codeLen = strlen(code);
    *outputTokens = (Token *)malloc(codeLen * sizeof(Token));  // выделяем максимальный размер памяти (считая, что количество токенов равно колличеству символов)
    // Хотя есть другой способ узнать число токенов заранее, как (количество операторов) * 2 + 1
    if (!*outputTokens) {
        printf("lexAnalysis malloc failure\n");
        exit(EXIT_FAILURE);
    }
    char ch;
    int tokensCount = 0;
    int lastPos = -1;
    for (int i = 0; i < codeLen; i++) {
        ch = code[i];
        if (ch == '+') {
            // Здесь i - индекс конца текущего токена, lastPos - индекс конца предыдущего токена
            // Тогда, начало текущего токена = lastPos+1
            APPEND_TOKEN(PLUS)
        }
        else if (isdigit(ch)) {
            if (i == codeLen - 1) {
                APPEND_TOKEN(NUMBER)
                break;
            }
            char nextCh = code[i+1];
            if (!isdigit(nextCh)) {
                APPEND_TOKEN(NUMBER)
            }
            // else токен не завершён, число не сформировано
        }
        else {
            printf("Undefined token\n");
            exit(EXIT_FAILURE);
        }
    }
    realloc(outputTokens, tokensCount * sizeof(Token));  // оптимизация, освобождение лишней памяти
    return tokensCount;
}

#undef APPEND_NUMBER