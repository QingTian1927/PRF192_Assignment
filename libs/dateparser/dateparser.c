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

struct dateObj {
    short int year;
    short int month;
    short int day;
};

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

int isValidDay(short int day, short int currentMonth, int isLeapYear) {
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
            result = (isLeapYear) ? (day <= 28) : (day <= 29);
            break;
        default:
            return -1;
    }
    return result;
}
