#include <stdio.h>
#include <stdlib.h>

int doesFileExist(char* fileName) {
    FILE* filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        return 0;
    }
    return 1;
}
