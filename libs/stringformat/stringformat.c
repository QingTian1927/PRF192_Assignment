/**
 * @file stringFormat.c
 * @author QingTian
 * @brief string formatting related functions
 */

// ! NOTE: the length of a string is defined as the number of characters
// !       within that string EXCLUDING the null terminator.
// !
// !       This is the same as the result of <string.h> strlen()

#include <stddef.h>  // For NULL value
#include "stringformat.h"

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

/**
 * @brief Directly capitalizes all words in a string.
 * @author L. Nga.
 *
 * Nga's implementation of the capitalizeString(). Both functions are
 * fundamentally equivalent, except for the fact that upper1stltr() is not
 * portable. This is simply because strlwr() is a non-standard function built
 * into older versions of Microsoft C.
 *
 * Nevertheless, were one to compile this with Dev-C++ using its custom GCC
 * compiler, the code would execute just fine. Thus, credit must be given where
 * credit is due.
 *
 * NOTE: the original code has been reformatted a bit to make it more readable.
 *       Other than that, nothing else have been changed.
 *
 * @param arr The string to be capitalized.
 */

/*

void upper1stltr(char arr[]){
    int i;
    strlwr(arr);

    for (i = 0; i < strlen(arr); i++){
        if(arr[i] == ' ' && isalpha(arr[i + 1]) !=0 ) {
            arr[i + 1] = toupper(arr[i + 1]);
        }
        else if(i == 0 && isalpha(arr[i]) != 0) {
            arr[i] = toupper(arr[i]);
        }
        else { continue };
    }
}

*/

int trimLeft(char* str, int len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    int whiteSpaces = 0;
    while (isWhiteSpace(str[whiteSpaces]) && whiteSpaces <= len) {
        whiteSpaces++;
    }
    if (whiteSpaces <= 0) { return len; }

    int i = 0;
    while (i <= len) {
        // Shifts string to the left
        str[i] = str[i + whiteSpaces];
        i++;
    }
    str[i] = '\0';

    int newLen = len - whiteSpaces;
    return newLen;
}

int trimRight(char* str, int len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    int i = len - 1;  // To account for zero-based indexing
    while (isWhiteSpace(str[i]) && i >= 0) {
        i--;
    }

    // Null terminates string on the right
    str[i + 1] = '\0';
    int newLen = i + 1;
    return newLen;
}

int trimInner(char* str, int len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    int i = 0;
    int whiteSpaces = 0;
    while (i <= len) {
        if (isWhiteSpace(str[i]) == 0) {
            whiteSpaces = 0;
            i++;
            continue;
        }

        // Count the number of spaces between two words
        int j = i;
        while (isWhiteSpace(str[j]) && j <= len) {
            whiteSpaces++;
            j++;
        }

        // One space between words is valid
        if (whiteSpaces <= 1) {
            i++;
            continue;
        }
        int invalidSpaces = whiteSpaces - 1;

        for (j = i; j <= len - invalidSpaces; j++) {
            // Shift array to the left
            str[j] = str[j + invalidSpaces];
        }
        len -= invalidSpaces;
        i++;
    }
    str[len] = '\0';
    return len;
}

int fullTrim(char* str, int len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    len = trimLeft(str, len);
    len = trimRight(str, len);
    len = trimInner(str, len);

    return len;
}
