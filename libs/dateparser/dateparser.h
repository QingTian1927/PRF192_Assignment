#ifndef _DATEPARSER_H_
#define _DATEPARSER_H_

#define UNIQUE_SUPPORTED_SPECIFIERS 3

#define MAX_YEAR 9999
#define MAX_MONTH 12
#define MAX_DAY 31

#define MAX_YEAR_SPECIFIERS 4
#define MAX_MONTH_SPECIFIERS 2
#define MAX_DAY_SPECIFIERS 2
#define MAX_DATE_STRING 10  // max specifiers + 2 separators

struct parserSettings {
    char* specifierOrder;
    char isPaddedDay;
    char isPaddedMonth;
};
int getDayFormat(struct parserSettings settingsPtr);
int getMonthFormat(struct parserSettings settingsPtr);
void setDayFormat(struct parserSettings* settingsPtr, int isPadded);
void setMonthFormat(struct parserSettings* settingsPtr, int isPadded);

int parseFormatString(
    char* formatString,
    int strLen,
    const char separator,
    struct parserSettings* settingsPtr
);

#endif
