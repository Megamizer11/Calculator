#include <stdio.h>
#include <stdlib.h>

void raiseError(bool condition, const char* message) {
    if (condition) {
        printf(message);
        exit(EXIT_FAILURE);
    }
}