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

#include <stddef.h>  // For NULL value
#include "dateParser.h"

#define YEAR_SPECIFIER 'y'
#define MONTH_SPECIFIER 'M'
#define DAY_SPECIFIER 'd'

#define FORMAT_ERROR -1
#define PADDING_NONE 0
#define PADDING_REQUIRED 1

#define FOUR_DIGIT_YEARS 4

#define MONTH_NO_PADDING 1
#define MONTH_WITH_PADDING 2

#define DAY_NO_PADDING 1
#define DAY_WITH_PADDING 2

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
        case MONTH_NO_PADDING:
            setMonthFormat(settingsPtr, PADDING_NONE);
            break;
        case MONTH_WITH_PADDING:
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
        case DAY_NO_PADDING:
            setDayFormat(settingsPtr, PADDING_NONE);
            break;
        case DAY_WITH_PADDING:
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
            case YEAR_SPECIFIER:
                yearSpecifiers++;
                break;
            case MONTH_SPECIFIER:
                monthSpecifiers++;
                break;
            case DAY_SPECIFIER:
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