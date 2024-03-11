#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/database/database.h"
#include "libs/userinterface/userinterface.h"

#include "libs/cheflist/cheflist.h"
#include "libs/chefobject/chefobject.h"

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
#define EDIT_ANOTHER '5'

#define SEARCH_NAME '1'
#define SEARCH_SALARY '2'

#define DISPLAY_ACTUAL '1'
#define DISPLAY_NAME '2'
#define DISPLAY_SALARY '3'

#define LOAD_FILE_MANUAL 0
#define LOAD_FILE_STARTUP 1

#define FALLBACK_SAVE_FILE "fallback_save.chefs"
#define MAX_SAVE_RETRIES 3
#define MAX_REALLOCATION_RETRIES 3

chefFileObj* loadFileWrapper(char* fileNameSavePtr, int option);
int saveFileWrapper(char* savedFileName, chefObj ** chefList, int listLen);
void manualSaveHandler(char* fileName, chefObj ** chefList, int listLen, int* modStatusPtr);

void totalSalaryWrapper(chefObj ** chefList, int listLen);

void editListWrapper(chefObj *** chefListPtr, int* listLenPtr);
void addChefWrapper(chefObj *** chefListPtr, int* listLenPtr);
char editChefWrapper(chefObj ** chefList, int listLen);
void removeChefWrapper(chefObj ** chefList, int listLen);

void editNameWrapper(chefObj* chefPtr);
void editRoleWrapper(chefObj* chefPtr);
void editDateWrapper(chefObj* chefPtr);
void editSalaryWrapper(chefObj* chefPtr);

void searchChefsWrapper(chefObj ** chefList, int listLen);
void searchNameWrapper(chefObj ** chefList, int listLen);
void searchSalaryWrapper(chefObj ** chefList, int listLen);
void handleSearchResult(chefSearchResult* searchResult, chefObj ** chefList, int listLen);

void displayChefsWrapper(chefObj ** chefList, int listLen);
void displayActualWrapper(chefObj ** chefList, int listLen);
void displaySortedWrapper(chefObj ** chefList, int listLen, char sortKey);

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
                searchChefsWrapper(chefList, listLen);
                break;
            case EDIT_CHEF_LIST:
                editListWrapper(&chefList, &listLen);
                hasModifiedList = 1;
                break;
            case RUN_CALCULATIONS:
                totalSalaryWrapper(chefList, listLen);
                break;
            case MANUAL_SAVE:
                manualSaveHandler(
                    fileName,
                    chefList,
                    listLen,
                    &hasModifiedList
                );
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }

    if (hasModifiedList == 0) {
        freeChefList(chefList, listLen);
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
        freeChefList(chefList, listLen);
        free(chefFile);
        printf("All unsaved data has been discarded.\n");
        exit(EXIT_SUCCESS);
    }

    saveResult = saveFileWrapper(fileName, chefList, listLen);
    freeChefList(chefList, listLen);
    free(chefFile);

    if (saveResult == WRITE_FILE_FAIL) {
        printf("Failed to save data to fallback location.\n");
        printf("All unsaved data has been discarded.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/* FOCUS */
chefFileObj* loadFileWrapper(char* fileNameSavePtr, int option) {
    int isInvalidOption = 0;
    int hasToLoadFile = -1;

    if (option == LOAD_FILE_MANUAL) { hasToLoadFile = 1; }

    /* IGNORE */
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
    /* IGNORE */

    if (hasToLoadFile <= 0) { return NULL; }

    printf("\nPlease enter the path to the chef file [max %d characters]:\n", MAX_PATH_LEN);
    printf("> ");
    int result = getStringInput(fileNameSavePtr, MAX_PATH_LEN + 1);
    printf("\n");

    if (result == -1) {
        printf("-> Failed to register the file path\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    int checkFileResult = doesFileExist(fileNameSavePtr);
    if (checkFileResult == FILE_NOTFOUND) {
        printf("-> The specified file could not be located\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    chefFileObj* chefFile = readChefsFile(fileNameSavePtr);
    if (chefFile == NULL) {
        printf("-> Experienced an error while trying to read from the specified file\n");
        pressEnterTo("continue to the main program");
        return NULL;
    }

    printf("-> Successfully loaded a chef list from the specified file\n");
    pressEnterTo("continue to the main program");

    return chefFile;
}
/* FOCUS */

/* FOCUS */
int saveFileWrapper(char* savedFileName, chefObj ** chefList, int listLen) {
    char fileName[MAX_PATH_LEN + 1];
    fileName[0] = '\0';

    int reuseFile = -1;
    int isInvalidOption = 0;

    if (strlen(savedFileName) > 0) {
        /* IGNORE */
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
        /* IGNORE */
        if (reuseFile) {
            strncpy(fileName, savedFileName, MAX_PATH_LEN + 1);
        }
    }

    if (reuseFile == 0 || strlen(savedFileName) <= 0) {
        int result = 0;
        while (result <= 0) {
            if (result == -1) {
                printf("-> Failed to register the file path\n\n");
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
            printf("\n-> Successfully saved the chef list to %s\n", fileName);
            return WRITE_FILE_OKAY;
        }
        printf("Attempt [%d] to write to %s failed!\n", attemptNo, fileName);
    }

    printf("\n-> Failed to write to %s after %d retries!\n\n", fileName, MAX_SAVE_RETRIES);
    printf("Attempting to save to fallback location ...\n");

    for (attemptNo = 1; attemptNo <= MAX_SAVE_RETRIES; attemptNo++) {
        int writeResult = writeChefsFile(FALLBACK_SAVE_FILE, chefList, listLen);

        if (writeResult == WRITE_FILE_OKAY) {
            printf("\n-> Successfully saved the chef list to %s\n", FALLBACK_SAVE_FILE);
            return WRITE_FILE_OKAY;
        }
        printf("Attempt [%d] to write to %s failed!\n", attemptNo, FALLBACK_SAVE_FILE);
    }

    return WRITE_FILE_FAIL;
}
/* FOCUS */

void manualSaveHandler(
    char* fileName,
    chefObj ** chefList,
    int listLen,
    int* modStatusPtr
) {
    int saveResult = saveFileWrapper(fileName, chefList, listLen);
    if (saveResult == WRITE_FILE_OKAY) {
        if (*modStatusPtr == 1) {
            *modStatusPtr = 0;
        }
        pressEnterTo("continue");
        return;
    }

    printf("Failed to write to specified file and fallback file!\n");
    printf("Please check your working directory and try again.\n");
    pressEnterTo("continue");
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

    editNameWrapper(chef);
    printf("-> NAME: %s\n\n", getName(chef));

    editRoleWrapper(chef);
    printf("-> ROLE: %s\n\n", getRole(chef));

    editDateWrapper(chef);
    printf("-> D.O.B: %s\n\n", getDateOfBirth(chef));

    editSalaryWrapper(chef);
    printf("-> SALARY: %ld\n\n", getSalary(chef));

    int listStatus = checkChefListStatus(chefList, listLen);
    if (listStatus == CHEFLIST_FULL) {
        int newLen = listLen + DEFAULT_CHEFLIST_SIZE;
        chefObj ** resizedList = resizeChefList(chefList, listLen, newLen);

        if (resizedList == NULL) {
            printf("Failed to resize the chef list for the new chef!\n");
            printf("Please try again later or restart the program.\n");
            pressEnterTo("return to the menu");
            free(chef);
            return;
        }

        listLen = newLen;
        chefList = resizedList;
        *listLenPtr = newLen;
        *chefListPtr = resizedList;
    }

    int insertionResult = insertChefIntoList(chefList, listLen, chef);
    if (insertionResult == APPEND_CHEF_OKAY) {
        printf("Successfully added the new chef to the list!\n");
        pressEnterTo("return to the menu");
        return;
    }

    if (insertionResult == APPEND_CHEF_FAIL) {
        printf("Failed to add the new chef to the list!\n");
        printf("Please try again later or restart the program.\n");
        pressEnterTo("return to the menu");
        free(chef);
        return;
    }
}

void removeChefWrapper(chefObj ** chefList, int listLen) {
    clearScreen();
    printTitleCard();

    int chefCount = countChefsInList(chefList, listLen);
    if (chefCount == 0) {
        printf("Cannot remove any chef as the list is empty ...\n");
        pressEnterTo("return to the menu");
        return;
    }

    printf("Please find the number of the chef to be removed from the list:\n\n");

    if (listLen <= DEFAULT_CHEFLIST_SIZE) {
        printUnsortedChefList(chefList, listLen, DISABLE_PAGER);
    } else {
        printUnsortedChefList(chefList, listLen, ENABLE_PAGER);
    }
    printf("\n");

    int position = 0;
    while (position <= 0) {
        if (position == -1) {
            printf("-> You've entered an invalid value!\n\n");
            position = 0;
        }
        printf("Enter the number of the chef to be removed [1 -> %d]:\n", listLen);
        printf("> ");

        position = getLongInput();
        flushBuffer();
        printf("\n");

        if (position < 1 || position > listLen) { position = -1; }
    }

    int index = position - 1;
    deleteChef(&chefList[index]);

    shiftListLeft(chefList, listLen, index, 1);

    printf("-> Removed chef number %d from the list\n", position);
    pressEnterTo("return to continue");
}

void totalSalaryWrapper(chefObj ** chefList, int listLen) {
    clearScreen();
    printTitleCard();

    int chefCount = countChefsInList(chefList, listLen);
    if (chefCount == 0) {
        printf("Cannot perform calculation as the list is empty ...\n");
        pressEnterTo("return to the menu");
        return;
    }
    long long total = calculateChefTotalSalary(chefList, listLen);

    printf("The total salary of %d chef(s) is:\n\n", chefCount);
    printf("-> %lld\n", total);
    pressEnterTo("return to the menu");
}

void editNameWrapper(chefObj* chefPtr) {
    int inputResult = 0;
    int propertyResult = -1;
    char name[ACTUAL_MAX_NAME_LEN];

    while (propertyResult <= 0) {
        if (inputResult == -1) {
            printf("-> Failed to register the chef's name!\n\n");
            inputResult = 0;
        }
        else if (propertyResult == SET_PROPERTY_FAIL) {
            printf("-> You've entered an invalid name!\n\n");
            propertyResult = -1;
        }

        printf("Enter the name of the chef [max %d characters]:\n", MAX_NAME_LEN);
        printf("> ");

        inputResult = getStringInput(name, ACTUAL_MAX_NAME_LEN);
        if (strlen(name) >= MAX_NAME_LEN || inputResult == -1) {
            flushBuffer();
        }

        propertyResult = setName(chefPtr, name);
        printf("\n");
    }
}

void editRoleWrapper(chefObj* chefPtr) {
    int propertyResult = -1;

    while (propertyResult <= 0) {
        if (propertyResult == SET_PROPERTY_FAIL) {
            printf("-> Failed to register the chef's role\n\n");
            propertyResult = -1;
        }

        char* ROLES_TABLE[] = {
            "APPRENTICE COOK",
            "JUNIOR CHEF",
            "SEASONED CHEF",
            "MASTER CHEF"
        };

        printf("Assign the chef one of the following roles:\n\n");
        printf("1) %s\n", ROLES_TABLE[0]);
        printf("2) %s\n", ROLES_TABLE[1]);
        printf("3) %s\n", ROLES_TABLE[2]);
        printf("4) %s\n\n", ROLES_TABLE[3]);

        printf("Enter your choice: ");
        char choice = getchar();
        flushBuffer();
        printf("\n");

        switch (choice) {
            case '1':
                propertyResult = setRole(chefPtr, ROLES_TABLE[0]);
                break;
            case '2':
                propertyResult = setRole(chefPtr, ROLES_TABLE[1]);
                break;
            case '3':
                propertyResult = setRole(chefPtr, ROLES_TABLE[2]);
                break;
            case '4':
                propertyResult = setRole(chefPtr, ROLES_TABLE[3]);
                break;
            default:
                printf("-> Please enter a valid option\n\n");
        }
    }
}

void editDateWrapper(chefObj* chefPtr) {
    int inputResult = 0;
    int propertyResult = -1;
    char dob[ACTUAL_MAX_DATE_LEN];

    while (propertyResult <= 0) {
        if (inputResult == -1) {
            printf("-> Failed to register the chef's date of birth!\n\n");
            inputResult = 0;
        }
        else if (propertyResult == SET_PROPERTY_FAIL) {
            printf("-> You've entered an invalid date!\n\n");
            propertyResult = -1;
        }

        printf("Enter the date of birth of the chef [YYYY-MM-DD]:\n");
        printf("> ");

        inputResult = getStringInput(dob, ACTUAL_MAX_DATE_LEN);
        if (strlen(dob) >= MAX_DATE_LEN || inputResult == -1) {
            flushBuffer();
        }

        propertyResult = setDateOfBirth(chefPtr, dob);
        printf("\n");
    }
}

void editSalaryWrapper(chefObj* chefPtr) {
    int propertyResult = -1;
    long salary;

    while (propertyResult <= 0) {
        if (propertyResult == SET_PROPERTY_FAIL) {
            printf("-> You've entered an invalid value!\n\n");
            propertyResult = -1;
        }
        printf("Enter the salary of the chef [max %d]:\n", MAX_SALARY);
        printf("> ");

        salary = getLongInput();
        flushBuffer();

        propertyResult = setSalary(chefPtr, salary);
        printf("\n");
    }
}

char editChefWrapper(chefObj ** chefList, int listLen) {
    clearScreen();
    printTitleCard();

    int chefCount = countChefsInList(chefList, listLen);
    if (chefCount == 0) {
        printf("Cannot edit any chef as the list is empty ...\n");
        pressEnterTo("return to the menu");
        return EXIT_MENU;
    }

    printf("Please find the number of the chef to be edited:\n\n");

    if (listLen <= DEFAULT_CHEFLIST_SIZE) {
        printUnsortedChefList(chefList, listLen, DISABLE_PAGER);
    } else {
        printUnsortedChefList(chefList, listLen, ENABLE_PAGER);
    }
    printf("\n");

    int position = 0;
    while (position <= 0) {
        if (position == -1) {
            printf("-> You've entered an invalid value!\n\n");
            position = 0;
        }
        printf("Enter the number of the chef to be edited [1 -> %d]:\n", listLen);
        printf("> ");

        position = getLongInput();
        flushBuffer();
        printf("\n");

        if (position < 1 || position > listLen) { position = -1; }
    }

    int index = position - 1;
    chefObj* selectedChef = chefList[index];

    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        printf("Selected chef:\n\n");
        printf("> ");

        printf(
            "%0*d | %s | %s | %s | %ld\n\n",
            getNumLen(listLen), position,
            getName(selectedChef),
            getRole(selectedChef),
            getDateOfBirth(selectedChef),
            getSalary(selectedChef)
        );

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
                editNameWrapper(selectedChef);
                break;
            case EDIT_ROLE:
                editRoleWrapper(selectedChef);
                break;
            case EDIT_DOB:
                editDateWrapper(selectedChef);
                break;
            case EDIT_SAL:
                editSalaryWrapper(selectedChef);
                break;
            case EDIT_ANOTHER:
                return EDIT_ANOTHER;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
    return EXIT_MENU;
}

void editListWrapper(chefObj *** chefListPtr, int* listLenPtr) {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    char editChefStatus = EDIT_ANOTHER;

    while (hasNotExited) {
        chefObj ** chefList = *chefListPtr;
        int listLen = *listLenPtr;

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
                while (editChefStatus == EDIT_ANOTHER) {
                    editChefStatus = editChefWrapper(chefList, listLen);
                }
                // What a bloody hack
                break;
            case REMOVE_CHEF:
                removeChefWrapper(chefList, listLen);
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}

void handleSearchResult(
    chefSearchResult* searchResult,
    chefObj ** chefList,
    int listLen
) {
    if (searchResult == NULL) {
        printf("Experienced an error while trying to initiate search\n");
        printf("Please try again or restart the program\n");
        return;
    }

    chefObj ** resultList = searchResult->resultList;
    int resultLen = searchResult->resultLen;

    if (resultList == NULL || resultLen <= 0) {
        printf("-> Could not find any chefs with matching information.\n");
        free(resultList);
        free(searchResult);
        return;
    }

    short int maxNameLen, maxRoleLen, maxSalLen, maxDobLen, maxPosLen;

    maxLenObj* maxLens = getPropertiesMaxLen(resultList, resultLen);
    handleMaxLens(maxLens, resultLen);

    maxNameLen = maxLens->maxNameLen;
    maxRoleLen = maxLens->maxRoleLen;
    maxSalLen = maxLens->maxSalLen;
    maxDobLen = maxLens->maxDobLen;
    maxPosLen = maxLens->maxPosLen;

    short int maxLineLen = getMaxLineLen(maxLens);

    printTableHeader(maxLens);
    printHorizontalDivider("-", maxLineLen);

    int i;
    for (i = 0; i < resultLen; i++) {
        chefObj* currentChef = resultList[i];

        char* name = getName(currentChef);
        char* role = getRole(currentChef);
        char* dob = getDateOfBirth(currentChef);
        long sal = getSalary(currentChef);
        int idx = findChefOriginalIndex(chefList, listLen, currentChef);
        int pos = idx + 1;

        printf(
            "%0*d | %-*s | %-*s | %*s | %*ld\n",
            maxPosLen, pos,
            maxNameLen, name,
            maxRoleLen, role,
            maxDobLen, dob,
            maxSalLen, sal
        );
    }
    printf("\n");
    printf("-> Found a total of %d matching chef(s)\n", resultLen);

    free(maxLens);
    free(resultList);
    free(searchResult);
}

void searchSalaryWrapper(chefObj ** chefList, int listLen) {
    clearScreen();
    printTitleCard();

    int chefCount = countChefsInList(chefList, listLen);
    if (chefCount == 0) {
        printf("The list is currently empty ...\n");
        pressEnterTo("return to the menu");
        return;
    }

    long minSalary = -1;
    long maxSalary = -1;

    while (minSalary == -1) {
        printf("Enter the minimum salary to be searched [max %d]:\n", MAX_SALARY);
        printf("> ");

        minSalary = getLongInput();
        flushBuffer();
        printf("\n");

        if (minSalary < 0 || minSalary > MAX_SALARY) {
            printf("-> You've entered an invalid value!\n\n");
            minSalary = -1;
        }
    }

    while (maxSalary == -1) {
        printf("Enter the maximum salary to be searched [max %d]:\n", MAX_SALARY);
        printf("> ");

        maxSalary = getLongInput();
        flushBuffer();
        printf("\n");

        if (maxSalary < 0 || maxSalary > MAX_SALARY) {
            printf("-> You've entered an invalid value!\n\n");
            maxSalary = -1;
        }
    }

    chefSearchResult* searchResult = searchChefBySalaryRange(
        chefList, listLen, minSalary, maxSalary
    );
    handleSearchResult(searchResult, chefList, listLen);

    pressEnterTo("return to the menu");
}

void searchNameWrapper(chefObj ** chefList, int listLen) {
    clearScreen();
    printTitleCard();

    int chefCount = countChefsInList(chefList, listLen);
    if (chefCount == 0) {
        printf("The list is currently empty ...\n");
        pressEnterTo("return to the menu");
        return;
    }

    char query[ACTUAL_MAX_NAME_LEN];
    int inputResult = 0;

    while (inputResult <= 0) {
        if (inputResult == -1) {
            printf("-> Failed to register the query!\n\n");
            inputResult = 0;
        }

        printf("Enter the name of the chef to be searched [max %d characters]:\n", MAX_NAME_LEN);
        printf("> ");

        inputResult = getStringInput(query, ACTUAL_MAX_NAME_LEN);
        if (strlen(query) >= MAX_NAME_LEN || inputResult == -1) {
            flushBuffer();
        }
        printf("\n");
    }
    chefSearchResult* searchResult = searchChefByName(chefList, listLen, query);
    handleSearchResult(searchResult, chefList, listLen);

    pressEnterTo("return to the menu");
}

void searchChefsWrapper(chefObj ** chefList, int listLen) {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printSearchSubmenu(STANDARD_PROMPT);
        } else {
            printSearchSubmenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        flushBuffer();
        printf("\n");

        switch (choice) {
            case SEARCH_NAME:
                searchNameWrapper(chefList, listLen);
                break;
            case SEARCH_SALARY:
                searchSalaryWrapper(chefList, listLen);
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}

void displayActualWrapper(chefObj ** chefList, int listLen) {
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

void displaySortedWrapper(chefObj ** chefList, int listLen, char sortKey) {
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

    printSortedChefList(chefList, listLen, pagerOption, sortKey);
    pressEnterTo("continue to the main program");
}

void displayChefsWrapper(chefObj ** chefList, int listLen) {
    int hasNotExited = 1;
    int isInvalidOption = 0;

    while (hasNotExited) {
        clearScreen();
        printTitleCard();

        if (isInvalidOption == 0) {
            printDisplaySubmenu(STANDARD_PROMPT);
        } else {
            printDisplaySubmenu(INVALID_PROMPT);
            isInvalidOption = 0;
        }

        char choice = getchar();
        flushBuffer();
        printf("\n");

        switch (choice) {
            case DISPLAY_ACTUAL:
                displayActualWrapper(chefList, listLen);
                break;
            case DISPLAY_NAME:
                displaySortedWrapper(chefList, listLen, KEY_NAME);
                break;
            case DISPLAY_SALARY:
                displaySortedWrapper(chefList, listLen, KEY_SALARY);
                break;
            case EXIT_MENU:
                hasNotExited = 0;
                break;
            default:
                isInvalidOption = 1;
        }
    }
}
