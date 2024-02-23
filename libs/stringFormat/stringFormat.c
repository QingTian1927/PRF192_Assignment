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