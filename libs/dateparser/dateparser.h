/**
 * @file dateparser.h
 * @author QingTian
 * @brief header file for dateparser.c
 */

#ifndef _DATEPARSER_H_
#define _DATEPARSER_H_

#define UNIQUE_SPECIFIERS_NUM 3
#define DATE_SEPARATOR '-'
#define DATE_STRING_LEN 10

#define MAX_YEAR_LEN 4
#define MAX_MONTH_LEN 2
#define MAX_DAY_LEN 2

typedef struct {
    short int year;
    short int month;
    short int day;
} dateObj;

int isValidYear(short int year);
int isLeapYear(short int year);
int isValidMonth(short int month);
int isValidDay(short int day, short int currentMonth, int isLeapYear);

int isValidDateString(char* dateStr);
int isValidDateObj(dateObj* date);

dateObj* parseDateString(char* dateStr);
int isValidDateObj(dateObj* date);

#endif
