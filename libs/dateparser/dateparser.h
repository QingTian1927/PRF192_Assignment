#ifndef _DATEPARSER_H_
#define _DATEPARSER_H_

#define UNIQUE_SPECIFIERS_NUM 3
#define DATE_SEPARATOR '-'
#define DATE_STRING_LEN 10

struct dateObj {
    short int year;
    short int month;
    short int day;
};

struct dateObj* parseDateString(char* dateStr);
int isValidDate(char* dateStr);

int isValidYear(short int year);
int isLeapYear(short int year);
int isValidMonth(short int month);
int isValidDay(short int day, short int currentMonth, int isLeapYear);

#endif
