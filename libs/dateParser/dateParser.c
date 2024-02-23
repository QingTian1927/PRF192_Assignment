/**
 * @file dateParser.c
 * @author QingTian
 * @brief functions related to parsing date strings
 *
 * Supported format specifiers:
 *
 *   *) d / dd
 *   *) M / MM
 *   *) yyyy
 *
 * Note:
 *   A valid date format string is one which contain at least one specifier of
 *   each type. So, yyyy-M-dd would be valid but MM-dd would not.
 */

// ! NOTE: the length of a string is defined as the number of characters
// !       within that string EXCLUDING the null terminator.
// !
// !       This is the same as the result of <string.h> strlen()

#include <stddef.h>
#include "dateParser.h"

#define FORMAT_ERROR -1
#define PADDING_NONE 0
#define PADDING_REQUIRED 1

int getDayFormat(struct parserSettings settingsPtr) {
    int format = settingsPtr.isPaddedDay;
    return format;
}
int getMonthFormat(struct parserSettings settingsPtr) {
    int format = settingsPtr.isPaddedMonth;
    return format;
}

void setDayFormat(struct parserSettings* settingsPtr, int isPadded) {
    settingsPtr->isPaddedDay = isPadded;
}
void setMonthFormat(struct parserSettings* settingsPtr, int isPadded) {
    settingsPtr->isPaddedMonth = isPadded;
}
void setParserError(struct parserSettings* settingsPtr) {
    setMonthFormat(settingsPtr, FORMAT_ERROR);
    setDayFormat(settingsPtr, FORMAT_ERROR);
}

int interpretYearSpecifiers(
    int yearSpecifiers,
    struct parserSettings* settingsPtr
) {
    #define FOUR_DIGIT_YEARS 4

    switch (yearSpecifiers) {
        case FOUR_DIGIT_YEARS:
            return 1;
            break;
        default:
            setParserError(settingsPtr);
            return 0;
    }
}

int interpretMonthSpecifiers(
    int monthSpecifiers,
    struct parserSettings* settingsPtr
) {
    switch (monthSpecifiers) {
        case 1:
            setMonthFormat(settingsPtr, PADDING_NONE);
            break;
        case 2:
            setMonthFormat(settingsPtr, PADDING_REQUIRED);
            break;
        default:
            setParserError(settingsPtr);
            return 0;
    }
    return 1;
}

int interpretDaySpecifiers(
    int daySpecifiers,
    struct parserSettings* settingsPtr
) {
    switch (daySpecifiers) {
        case 1:
            setDayFormat(settingsPtr, PADDING_NONE);
            break;
        case 2:
            setDayFormat(settingsPtr, PADDING_REQUIRED);
            break;
        default:
            setParserError(settingsPtr);
            return 0;
    }
    return 1;
}

int parseFormatString(
    char* formatString,
    int strLen,
    const char separator,
    struct parserSettings* settingsPtr
) {
    const int PARSING_FAILED = 0;
    const int PARSING_SUCCESS = 1;

    if (formatString == NULL || strLen == 0) {
        setParserError(settingsPtr);
        return PARSING_FAILED;
    }

    int yearSpecifiers = 0;
    int monthSpecifiers = 0;
    int daySpecifiers = 0;

    int i;
    for (i = 0; i < strLen; i++) {
        if (formatString[i] == separator && separator != 0) { continue; }
        if (formatString[i] == '\0') { break; }
        switch (formatString[i]) {
            case 'y':
                yearSpecifiers++;
                break;
            case 'M':
                monthSpecifiers++;
                break;
            case 'd':
                daySpecifiers++;
                break;
            default:
                setParserError(settingsPtr);
                return PARSING_FAILED;
        }
    }

    int yearFormatResult = interpretYearSpecifiers(yearSpecifiers, settingsPtr);
    if (yearFormatResult == 0) { return PARSING_FAILED; }

    int monthFormatResult = interpretMonthSpecifiers(monthSpecifiers, settingsPtr);
    if (monthFormatResult == 0) { return PARSING_FAILED; }

    int dayFormatResult = interpretDaySpecifiers(daySpecifiers, settingsPtr);
    if (dayFormatResult == 0) { return PARSING_FAILED; }

    return PARSING_SUCCESS;
}