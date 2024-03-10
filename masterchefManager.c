#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/database/database.h"
#include "libs/userinterface/userinterface.h"

#include "libs/cheflist/cheflist.h"
#include "libs/chefobject/chefobject.h"

#include "libs/dateparser/dateparser.h"
#include "libs/stringformat/stringformat.h"

#define DISPLAY_CHEFS '1'
#define SEARCH_CHEFS '2'
#define EDIT_CHEF_LIST '3'
#define RUN_CALCULATIONS '4'
#define MANUAL_SAVE '5'
#define EXIT_MENU '0'

#define ADD_CHEF '1'
#define EDIT_CHEF '2'
#define REMOVE_CHEF '3'

#define EDIT_NAME '1'
#define EDIT_ROLE '2'
#define EDIT_DOB '3'
#define EDIT_SAL '4'

#define LOAD_FILE_MANUAL 0
#define LOAD_FILE_STARTUP 1

#define FALLBACK_SAVE_FILE "fallback_save.chefs"
#define MAX_SAVE_RETRIES 3
#define MAX_REALLOCATION_RETRIES 3

chefFileObj* loadFileWrapper(char* fileNameSavePtr, int option);
int saveFileWrapper(char* savedFileName, chefObj ** chefList, int listLen);

void displayChefsWrapper(chefObj ** chefList, int listLen);

void editListWrapper(chefObj *** chefListPtr, int* listLenPtr);
void addChefWrapper(chefObj *** chefListPtr, int* listLenPtr);

void editChefWrapper(chefObj ** chefList, int* listLenPtr) {
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
            case EDIT_NAME:
                break;
            case EDIT_ROLE:
                break;
            case EDIT_DOB:
                break;
            case EDIT_SAL:
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}

void removeChefWrapper(chefObj ** chefList, int listLen) {

}

void editListWrapper(chefObj *** chefListPtr, int* listLenPtr) {
    chefObj ** chefList = *chefListPtr;
    int listLen = *listLenPtr;

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
            case ADD_CHEF:
                addChefWrapper(chefListPtr, listLenPtr);
                break;
            case EDIT_CHEF:
                break;
            case REMOVE_CHEF:
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}

int main() {
    chefObj ** chefList = NULL;
    int listLen = DEFAULT_CHEFLIST_SIZE;

    char fileName[MAX_PATH_LEN + 1];  // Including null terminator
    fileName[0] = '\0';

    chefFileObj* chefFile = loadFileWrapper(fileName, LOAD_FILE_STARTUP);
    if (chefFile != NULL) {
        chefList = chefFile->chefList;
        listLen = chefFile->listLen;
    } else {
        chefList = newChefList(listLen);
        if (chefList == NULL) {
            exitOnFatalException("Failed to create a new chef list upon start up");
        }
    }

    int hasNotExited = 1;
    int isInvalidOption = 0;
    int hasModifiedList = 0;
    int saveResult;

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
            case DISPLAY_CHEFS:
                displayChefsWrapper(chefList, listLen);
                break;
            case SEARCH_CHEFS:
                break;
            case EDIT_CHEF_LIST:
                editListWrapper(&chefList, &listLen);
                hasModifiedList = 1;
                break;
            case RUN_CALCULATIONS:
                break;
            case MANUAL_SAVE:
                saveResult = saveFileWrapper(fileName, chefList, listLen);
                if (saveResult == WRITE_FILE_FAIL) {
                    printf("Failed to write to specified file and fallback file!\n");
                    printf("Please check you working directory and try again.\n");
                }
                pressEnterTo("continue");
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }

    if (hasModifiedList == 0) {
        free(chefList);
        free(chefFile);
        exit(EXIT_SUCCESS);
    }

    int saveOption = -1;
    isInvalidOption = 0;

    while (saveOption == -1) {
        clearScreen();
        printTitleCard();

        printf("You have potentially unsaved changes!\n");
        if (isInvalidOption == 0) {
            printf("Do you want to save now? [y/n]: ");
        } else {
            printf("%s", INVALID_YESNO_PROMPT);
            isInvalidOption = 0;
        }

        char choice = lower(getchar());
        flushBuffer();
        printf("\n");

        switch (choice) {
            case 'y':
                saveOption = 1;
                break;
            case 'n':
                saveOption = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }

    if (saveOption == 0) {
        free(chefList);
        free(chefFile);
        printf("All unsaved data has been discarded.\n");
        exit(EXIT_SUCCESS);
    }

    saveResult = saveFileWrapper(fileName, chefList, listLen);
    free(chefList);
    free(chefFile);

    if (saveResult == WRITE_FILE_FAIL) {
        printf("Failed to save data to fallback location.\n");
        printf("All unsaved data has been discarded.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
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
            printf("Do you wish to view the entire chef list at once? [y/n]: ");
        } else {
            printf("%s", INVALID_YESNO_PROMPT);
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

chefFileObj* loadFileWrapper(char* fileNameSavePtr, int option) {
    int isInvalidOption = 0;
    int hasToLoadFile = -1;

    if (option == LOAD_FILE_MANUAL) { hasToLoadFile = 1; }

    while (hasToLoadFile == -1) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printf("Do you want to load an existing chef file? [y/n]: ");
        } else {
            printf("%s", INVALID_YESNO_PROMPT);
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

    printf("\nPlease enter the path to the chef file [max %d characters]:\n", MAX_PATH_LEN);
    printf("> ");
    int result = getStringInput(fileNameSavePtr, MAX_PATH_LEN + 1);
    printf("\n");

    if (result == -1) {
        printf("> Failed to register the file path\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    int checkFileResult = doesFileExist(fileNameSavePtr);
    if (checkFileResult == FILE_NOTFOUND) {
        printf("> The specified file could not be located\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    chefFileObj* chefFile = readChefsFile(fileNameSavePtr);
    if (chefFile == NULL) {
        printf("> Experienced an error while trying to read from the specified file\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    printf("> Successfully loaded a chef list from the specified file\n");
    pressEnterTo("continue to the main program");

    return chefFile;
}

int saveFileWrapper(char* savedFileName, chefObj ** chefList, int listLen) {
    char fileName[MAX_PATH_LEN + 1];
    fileName[0] = '\0';

    int reuseFile = -1;
    int isInvalidOption = 0;

    if (strlen(savedFileName) > 0) {
        while (reuseFile == -1) {
            clearScreen();
            printTitleCard();

            printf("You originally loaded a chef list from %s\n", savedFileName);
            if (isInvalidOption == 0) {
                printf("Do you want to save to this file? [y/n]: ");
            } else {
                printf("%s", INVALID_YESNO_PROMPT);
                isInvalidOption = 0;
            }

            char choice = lower(getchar());
            flushBuffer();
            printf("\n");

            switch (choice) {
                case 'y':
                    reuseFile = 1;
                    break;
                case 'n':
                    reuseFile = 0;
                    break;
                default:
                    isInvalidOption = 1;
            }
        }
        if (reuseFile) {
            strncpy(fileName, savedFileName, MAX_PATH_LEN + 1);
        }
    }

    if (reuseFile == 0 || strlen(savedFileName) <= 0) {
        int result = 0;
        while (result <= 0) {
            if (result == -1) {
                printf("> Failed to register the file path\n\n");
                result = 0;
            }
            printf("Enter the path to the new chef file [max %d characters]:\n", MAX_PATH_LEN);
            printf("> ");

            result = getStringInput(fileName, MAX_PATH_LEN);
            printf("\n");
        }
    }

    printf("Attempting to save to the given location ...\n");
    int attemptNo;

    for (attemptNo = 1; attemptNo <= MAX_SAVE_RETRIES; attemptNo++) {
        int writeResult = writeChefsFile(fileName, chefList, listLen);

        if (writeResult == WRITE_FILE_OKAY) {
            printf("Successfully saved the chef list to %s\n", fileName);
            return WRITE_FILE_OKAY;
        }
        printf("Attempt [%d] to write to %s failed!\n", attemptNo, fileName);
    }

    printf("\nFailed to write to %s after %d retries!\n", fileName, MAX_SAVE_RETRIES);
    printf("Attempting to save to fallback location ...\n");

    for (attemptNo = 1; attemptNo <= MAX_SAVE_RETRIES; attemptNo++) {
        int writeResult = writeChefsFile(FALLBACK_SAVE_FILE, chefList, listLen);

        if (writeResult == WRITE_FILE_OKAY) {
            printf("\nSuccessfully saved the chef list to %s\n", FALLBACK_SAVE_FILE);
            return WRITE_FILE_OKAY;
        }
        printf("Attempt [%d] to write to %s failed!\n", attemptNo, FALLBACK_SAVE_FILE);
    }

    return WRITE_FILE_FAIL;
}

void addChefWrapper(chefObj *** chefListPtr, int* listLenPtr) {
    clearScreen();
    printTitleCard();

    chefObj ** chefList = *chefListPtr;
    int listLen = *listLenPtr;

    chefObj* chef = newChef();
    if (chef == NULL) {
        printf("Failed to allocate memory for the new chef\n");
        printf("Please try again later or restart the program.\n");
        pressEnterTo("return to the menu");
        return;
    }

    int inputResult = 0;
    int propertyResult = -1;
    char name[MAX_NAME_LEN + 1];

    while (inputResult <= 0 && propertyResult <= 0) {
        if (inputResult == -1) {
            printf("> Failed to register the chef's name!\n\n");
            inputResult = 0;
        }
        else if (propertyResult == SET_PROPERTY_FAIL) {
            printf("> You've entered an invalid name!\n\n");
            propertyResult = -1;
        }

        printf("Enter the name of the new chef [max %d characters]:\n", MAX_NAME_LEN);
        printf("> ");

        inputResult = getStringInput(name, MAX_NAME_LEN + 1);
        propertyResult = setName(chef, name);
        printf("\n");
    }

    propertyResult = -1;

    while (propertyResult <= 0) {
        if (propertyResult == SET_PROPERTY_FAIL) {
            printf("> Failed to register the chef's role\n\n");
            propertyResult = -1;
        }

        char* ROLES_TABLE[] = {
            "APPRENTICE COOK",
            "JUNIOR CHEF",
            "SEASONED CHEF",
            "MASTER CHEF"
        };

        printf("Assign the new chef one of the following roles:\n\n");
        printf("1) %s\n", ROLES_TABLE[0]);
        printf("2) %s\n", ROLES_TABLE[1]);
        printf("3) %s\n", ROLES_TABLE[2]);
        printf("4) %s\n\n", ROLES_TABLE[3]);

        printf("Enter your choice:\n");
        printf("> ");
        char choice = getchar();
        flushBuffer();
        printf("\n");

        switch (choice) {
            case '1':
                propertyResult = setRole(chef, ROLES_TABLE[0]);
                break;
            case '2':
                propertyResult = setRole(chef, ROLES_TABLE[1]);
                break;
            case '3':
                propertyResult = setRole(chef, ROLES_TABLE[2]);
                break;
            case '4':
                propertyResult = setRole(chef, ROLES_TABLE[3]);
                break;
            default:
                printf("> Please enter a valid option\n\n");
        }
    }

    inputResult = 0;
    propertyResult = -1;
    char dob[MAX_DATE_LEN + 1];

    while (inputResult <= 0 && propertyResult <= 0) {
        if (inputResult == -1) {
            printf("> Failed to register the chef's date of birth!\n\n");
            inputResult = 0;
        }
        else if (propertyResult == SET_PROPERTY_FAIL) {
            printf("> You've entered an invalid date!\n\n");
            propertyResult = -1;
        }

        printf("Enter the date of birth of the new chef [YYYY-MM-DD]:\n");
        printf("> ");

        inputResult = getStringInput(dob, MAX_DATE_LEN + 1);
        if (strlen(dob) != MAX_DATE_LEN) {
            inputResult = -1;
        }

        propertyResult = setDateOfBirth(chef, dob);
        printf("\n");
    }

    propertyResult = -1;
    long salary;

    while (propertyResult <= 0) {
        if (propertyResult == SET_PROPERTY_FAIL) {
            printf("> You've entered an invalid value!\n\n");
            propertyResult = -1;
        }
        printf("Enter the salary of the new chef [max %d]:\n", MAX_SALARY);
        printf("> ");

        salary = getLongInput();
        flushBuffer();

        propertyResult = setSalary(chef, salary);
        printf("\n");
    }

    int listStatus = checkChefListStatus(chefList, listLen);
    if (listStatus == CHEFLIST_FULL) {
        int newLen = listLen + DEFAULT_CHEFLIST_SIZE;
        chefObj ** resizedList = resizeChefList(chefList, listLen, newLen);

        if (resizedList == NULL) {
            printf("Failed to resize the chef list for the new chef\n");
            printf("Please try again later or restart the program.\n");
            pressEnterTo("return to the menu");
            free(chef);
            return;
        }

        listLen = newLen;
        *listLenPtr = listLen;
        chefList = resizedList;
        *chefListPtr = chefList;
    }

    int insertionResult = insertChefIntoList(chefList, listLen, chef);
    if (insertionResult == APPEND_CHEF_OKAY) {
        printf("Successfully added the new chef to the list\n");
        pressEnterTo("return to the menu");
        return;
    }

    if (insertionResult == APPEND_CHEF_FAIL) {
        printf("Failed to add the new chef to the list\n");
        printf("Please try again later or restart the program.\n");
        pressEnterTo("return to the menu");
        free(chef);
        return;
    }
}