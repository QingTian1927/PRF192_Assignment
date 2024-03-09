#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/database/database.h"
#include "libs/userinterface/userinterface.h"

#include "libs/cheflist/cheflist.h"
#include "libs/chefobject/chefobject.h"

#include "libs/dateparser/dateparser.h"
#include "libs/stringformat/stringformat.h"

void editChefWrapper() {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printEditSubmenu(STANDARD_PROMPT);
        } else {
            printEditSubmenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        printf("\n");

        switch (choice) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '0':
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}

int main() {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printMainMenu(STANDARD_PROMPT);
        } else {
            printMainMenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        printf("\n");

        switch (choice) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '0':
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }

    exit(EXIT_SUCCESS);
}