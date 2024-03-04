/**
 * @file dateParser.c
 * @author QingTian
 * @brief functions related to parsing date strings
 *
 * Default date format: YYYY-MM-DD
 */

// ! NOTE: the length of a string is defined as the number of characters
// !       within that string EXCLUDING the null terminator.
// !
// !       This is the same as the result of <string.h> strlen()

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "dateparser.h"

struct dateObj* parseDateString(char* dateStr, int len) {
    if (len != DATE_STRING_LEN || dateStr == NULL) { return NULL; }

    struct dateObj* newDate = (struct dateObj*) malloc(sizeof(struct dateObj));
    if (newDate == NULL) { return NULL; }

    short int year, month, day;
    int parsingResult = sscanf(dateStr, "%hd-%hd-%hd", &year, &month, &day);
    if (parsingResult != 3) { return NULL; }

    newDate->year = year;
    newDate->month = month;
    newDate->day = day;

    return newDate;
}

int isValidDate(char* dateStr, int len) {
    if (len != DATE_STRING_LEN || dateStr == NULL) { return 0; }

    short int year, month, day;
    int parsingResult = sscanf(dateStr, "%hd-%hd-%hd", &year, &month, &day);
    if (parsingResult != 3) { return 0; }

    int isValidDateString = (
        isValidYear(year) && isValidMonth(month) &&
        isValidDay(day, month, year)
    );
    return isValidDateString;
}

int isValidYear(short int year) {
    int result = (year >= 1900);
    return result;
}

int isLeapYear(short int year) {
    int result = (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
    return result;
}

int isValidMonth(short int month) {
    int result = month >= 1 && month <= 12;
    return result;
}

int isValidDay(short int day, short int currentMonth, int currentYear) {
    if (day <= 0) { return -1; }

    int result = 0;
    switch (currentMonth) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            result = day <= 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            result = day <= 30;
            break;
        case 2:
            result = (isLeapYear(currentYear)) ? (day <= 29) : (day <= 28);
            break;
        default:
            return -1;
    }
    return result;
}
