/**
 * @file stringFormat.c
 * @author QingTian
 * @brief string formatting related functions
 */

// ! NOTE: the length of a string is defined as the number of characters
// !       within that string EXCLUDING the null terminator.
// !
// !       This is the same as the result of <string.h> strlen()

#include "stringFormat.h"

#define LOWER_UPPER_OFFSET 32 // 'a' - 'A'

/**
 * @brief Converts a lowercase ASCII letter to uppercase.
 *
 * Converts a lowercase letter to uppercase by subtracting the ASCII difference
 * between these two types of letter.
 *
 * If the input character is not a lowercase character, simply returns the
 * input character itself.
 *
 * @param ch - The character to be converted to uppercase.
 * @return char - The uppercased character.
 */
char upper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return (ch - LOWER_UPPER_OFFSET);
    }
    return ch;
}

/**
 * @brief Converts an uppercase ASCII letter to lowercase.
 *
 * Converts an uppercase letter to lowercase by subtracting the ASCII
 * difference between these two types of letter.
 *
 * If the input character is not an uppercase character, simply returns the
 * input character itself.
 *
 * @param ch - The character to be converted to lowercase.
 * @return char - The lowercased character.
 */
char lower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return (ch + LOWER_UPPER_OFFSET);
    }
    return ch;
}

/**
 * @brief Checks if a character is a white space character.
 *
 * Checks whether a given character is one of the following white space
 * characters:
 *
 *   *) ' '  - space
 *   *) '\t' - horizontal tab
 *   *) '\v' - vertical tab
 *   *) '\f' - feed
 *   *) '\n' - newline
 *   *) '\r' - carriage return
 *
 * @param ch - The character to be checked.
 * @return int result - 0 if is not white space.
 *                    - 1 if is white space.
 */
int isWhiteSpace(char ch) {
    switch (ch) {
        case ' ':
        case '\t':
        case '\v':
        case '\f':
        case '\n':
        case '\r':
            return 1;
        default:
            return 0;
    }
}

/**
 * @brief Directly capitalizes all words in a string.
 *
 * Capitalizes all words in a string by directly accessing the characters in
 * the array and then modifying it accordingly.
 *
 * E.g: Lorem ipsum dolor sit amet -> Lorem Ipsum Dolor Sit Amet
 *
 * @param str The string to be capitalized.
 * @param len The length of the string to be capitalized.
 */
void capitalizeString(char* str, int len) {
    int isNewWord = 1;
    int i;
    for (i = 0; i <= len; i++) {
        if (isWhiteSpace(str[i])) {
            isNewWord = 1;
            continue;
        }
        if (isNewWord) {
            str[i] = upper(str[i]);
            isNewWord = 0;
            continue;
        }
        str[i] = lower(str[i]);
    }
}