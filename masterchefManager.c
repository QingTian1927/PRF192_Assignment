#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/database/database.h"
#include "libs/userinterface/userinterface.h"

#include "libs/cheflist/cheflist.h"
#include "libs/chefobject/chefobject.h"

#include "libs/dateparser/dateparser.h"
#include "libs/stringformat/stringformat.h"

chefFileObj* loadChefFileOnStartup(void) {
    int isInvalidOption = 0;
    int hasToLoadFile = -1;

    while (hasToLoadFile == -1) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printf("Do you want to load an existing chef file? [y/n]: ");
        } else {
            printf("Invalid option. Please try again [y/n]: ");
            isInvalidOption = 0;
        }
        char choice = lower(getchar());
        flushBuffer();

        switch (choice) {
            case 'y':
                hasToLoadFile = 1;
                break;
            case 'n':
                hasToLoadFile = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }

    if (hasToLoadFile <= 0) { return NULL; }

    char fileName[MAX_PATH_LEN + 1];  // Including null terminator
    printf("Please enter the path to the chef file [max %d characters]: ", MAX_PATH_LEN);

    int result = getStringInput(fileName, MAX_PATH_LEN);
    printf("\n");

    if (result == -1) {
        printf("> Failed to register the file path\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    int checkFileResult = doesFileExist(fileName);
    if (checkFileResult == FILE_NOTFOUND) {
        printf("> The specified file could not be located\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    chefFileObj* chefFile = readChefsFile(fileName);
    if (chefFile == NULL) {
        printf("> Experienced an error while trying to read from the specified file\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    printf("> Successfully loaded a list of chefs from the specified file\n");
    pressEnterTo("continue to the main program");

    return chefFile;
}

void displayChefsWrapper(chefObj ** chefList, int listLen) {
    int isInvalidOption = 0;
    int pagerOption = -1;

    if (listLen <= DEFAULT_PAGE_SIZE) {
        pagerOption = DISABLE_PAGER;
        clearScreen();
        printTitleCard();
    }

    while (pagerOption == -1) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printf("Do you want to view the entire chef list at once? [y/n]: ");
        } else {
            printf("Invalid option. Please try again [y/n]: ");
            isInvalidOption = 0;
        }
        char choice = lower(getchar());
        flushBuffer();

        switch (choice) {
            case 'y':
                pagerOption = DISABLE_PAGER;
                break;
            case 'n':
                pagerOption = ENABLE_PAGER;
                break;
            default:
                isInvalidOption = 1;
        }
    }
    if (listLen > DEFAULT_PAGE_SIZE) { printf("\n"); }

    printUnsortedChefList(chefList, listLen, pagerOption);
    pressEnterTo("continue to the main program");
}

void editChefWrapper() {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printEditChefSubmenu(STANDARD_PROMPT);
        } else {
            printEditChefSubmenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        flushBuffer();
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

void editListWrapper(chefObj ** chefList, int listLen) {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printEditListSubmenu(STANDARD_PROMPT);
        } else {
            printEditListSubmenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        flushBuffer();
        printf("\n");

        switch (choice) {
            case '1':
                break;
            case '2':
                break;
            case '3':
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

    chefObj ** chefList = NULL;
    int listLen = 9;

    chefFileObj* chefFile = loadChefFileOnStartup();
    if (chefFile != NULL) {
        chefList = chefFile->chefList;
        listLen = chefFile->listLen;
    } else {
        chefList = newChefList(listLen);
        if (chefList == NULL) {
            exitOnFatalException("Failed to create a new chef list upon start up");
        }
    }

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
        flushBuffer();
        printf("\n");

        switch (choice) {
            case '1':
                displayChefsWrapper(chefList, listLen);
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

    free(chefList);
    free(chefFile);

    exit(EXIT_SUCCESS);
}