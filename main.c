#include <stdio.h>
#include "Lexer.h"

int main(int argc, const char *argv[]) {
    printf("Hello world\n");
    Token* tokens = NULL;
    int tokensCount = lexAnalysis("1+1+156", &tokens);
    for (int i = 0; i < tokensCount; i++) {
        print(tokens[i]);
    }
    free(tokens);
    return 0;
}