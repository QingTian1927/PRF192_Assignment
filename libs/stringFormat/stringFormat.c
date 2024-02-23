/**
 * @file stringFormat.c
 * @author QingTian
 * @brief string formatting related functions
 */

#include "stringFormat.h"

#define LOWER_UPPER_OFFSET 32 // 'a' - 'A'

char upper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return (ch - LOWER_UPPER_OFFSET);
    }
    return ch;
}

char lower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return (ch + LOWER_UPPER_OFFSET);
    }
    return ch;
}

int isWhiteSpace(char ch) {
    switch (ch) {
        case ' ':   // space
        case '\t':  // horizontal tab
        case '\v':  // vertical tab
        case '\f':  // feed
        case '\n':  // newline
        case '\r':  // carriage return
            return 1;
        default:
            return 0;
    }
}