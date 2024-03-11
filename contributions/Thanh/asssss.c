#include <stdio.h>

struct date {
    short int year;
    short int month;
    short int day;
};

char* format_date(struct date d) {
    static char formatted_date[11]; 
    sprintf(formatted_date, "%d-%d-%d", d.year, d.month, d.day);
    return formatted_date;
}

int main() {
    struct date my_date = {2024, 12, 23};
    char* formatted = format_date(my_date);
    printf("Formatted date: %s\n", formatted);
    return 0;
}

