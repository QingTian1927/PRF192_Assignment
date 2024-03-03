#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flushBuffer(void) {
    while (getchar() != '\n');
}

int getIntInput(void) {
    int num;
    while (scanf(" %d", &num) != 1) {
        printf("Invalid input. Please try again: ");
        flushBuffer();
    }
    return num;
}

double getDoubleInput(void) {
    double num;
    while (scanf(" %lf", &num) != 1) {
        printf("Invalid input. Please try again: ");
        flushBuffer();
    }
    return num;
}

size_t getStringInput(char* strPtr, int maxLen) {
    if (fgets(strPtr, maxLen, stdin) != NULL) {
        size_t len = strlen(strPtr);
        if (len > 0 && strPtr[len - 1] == '\n') {
            strPtr[len - 1] = '\0';
            return strlen(strPtr);
        }
    }
    printf("\n");
    printf("getStringInput() fgets() returned NULL.\n");
    printf("Process terminated unexpectedly.\n\n");
    exit(1);
}
