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
#include <stdlib.h>
#include <string.h>

#include "dateparser.h"

int isValidYear(short int year) {
    int result = year >= 1900 && year <= 9999;
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

dateObj* parseDateString(char* dateStr) {
    int len = strlen(dateStr);

    if (len != DATE_STRING_LEN || dateStr == NULL) { return NULL; }

    dateObj* newDate = (dateObj*) malloc(sizeof(dateObj));
    if (newDate == NULL) { return NULL; }

    short int year, month, day;
    int parsingResult = sscanf(dateStr, "%hd-%hd-%hd", &year, &month, &day);
    if (parsingResult != 3) { return NULL; }

    newDate->year = year;
    newDate->month = month;
    newDate->day = day;

    return newDate;
}

int isValidDateString(char* dateStr) {
    int len = strlen(dateStr);
    if (len != DATE_STRING_LEN || dateStr == NULL) { return 0; }

    short int year, month, day;
    int parsingResult = sscanf(dateStr, "%hd-%hd-%hd", &year, &month, &day);
    if (parsingResult != 3) { return 0; }

    int isValidDate = (
        isValidYear(year) && isValidMonth(month) &&
        isValidDay(day, month, year)
    );
    return isValidDate;
}

int isValidDateObj(dateObj* date) {
    if (date == 0) { return 0; }

    short int year = date->year;
    short int month = date->month;
    short int day = date->day;

    int isValidDate = (
        isValidYear(year) &&
        isValidMonth(month) &&
        isValidDay(day, month, year)
    );
    return isValidDate;
}

char* convertToDateString(dateObj* date) {
    int isInvalidParameter = date == NULL || !isValidDateObj(date);
    if (isInvalidParameter) { return NULL; }

    int actualLen = DATE_STRING_LEN + 1;
    char* dateStr = (char*) calloc(actualLen, sizeof(char));
    if (dateStr == NULL) { return NULL; }

    short int year = date->year;
    short int month = date->month;
    short int day = date->day;

    sprintf(dateStr, "%hd-%02hd-%02hd", year, month, day);

    dateStr[DATE_STRING_LEN] = '\0';
    return dateStr;
}
