/**
 * @file userinterface.c
 * @author QingTian
 * @brief functions relating to the user interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userinterface.h"

void exitOnFatalException(const char* message) {
	printf("[FATAL] %s\n", message);
	printf("Process terminated unconditionally.\n");
	exit(EXIT_FAILURE);
}

void flushBuffer(void) {
    while (getchar() != '\n');
}

void clearScreen(void) {
    printf("\e[1;1H\e[2J");
}

int getIntInput(void) {
    int num;
    while (scanf(" %d", &num) != 1) {
        printf("Invalid input. Please try again: ");
        flushBuffer();
    }
    return num;
}

long getLongInput(void) {
    long num;
    while (scanf(" %ld", &num) != 1) {
        printf("Invalid input. Please try again: ");
        flushBuffer();
    }
    return num;
}

double getDoubleInput(void) {
    double num;
    while (scanf(" %lf", &num) != 1) {
        printf("Invalid input. Please try again: ");
        flushBuffer();
    }
    return num;
}

int getStringInput(char* strPtr, int maxLen) {
    if (fgets(strPtr, maxLen, stdin) != NULL) {
        int len = strlen(strPtr);
        if (len > 0 && strPtr[len - 1] == '\n') {
            strPtr[len - 1] = '\0';
            return strlen(strPtr);
        }
        return len;
    }
    return -1;
}

void printHorizontalDivider(const char* ch, int maxLineLen) {
    int i;
    for (i = 0; i <= maxLineLen; i++) {
        printf("%s", ch);
    }
    printf("\n");
}

maxLenObj* getPropertiesMaxLen(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return NULL; }

    maxLenObj* maxLens = malloc(sizeof(maxLenObj));
    if (maxLens == NULL) { return NULL; }

    short int maxName = 0;
    short int maxRole = 0;
    short int maxSal = 0;

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char* name = getName(chefList[i]);
        char* role = getRole(chefList[i]);
        long sal = getSalary(chefList[i]);

        short int nameLen = strlen(name);
        short int roleLen = strlen(role);
        short int salLen = getNumLen(sal);

        maxName = (nameLen > maxName) ? nameLen : maxName;
        maxRole = (roleLen > maxRole) ? roleLen : maxRole;
        maxSal = (salLen > maxSal) ? salLen : maxSal;
    }

    maxLens->maxNameLen = maxName;
    maxLens->maxRoleLen = maxRole;
    maxLens->maxSalLen = maxSal;
    maxLens->maxDobLen = MAX_DATE_LEN;
    maxLens->maxPosLen = getNumLen(listLen - 1);

    return maxLens;
}

int handleMaxLens(maxLenObj* maxLens, int listLen) {
    if (maxLens == NULL) {
        maxLens->maxNameLen = MAX_NAME_LEN;
        maxLens->maxRoleLen = MAX_ROLE_LEN;
        maxLens->maxSalLen = MAX_SALARY_LEN;
        maxLens->maxDobLen = MAX_DATE_LEN;
        maxLens->maxPosLen = getNumLen(listLen - 1);
        return MAXLENS_REGULAR;
    }

    short int maxNameLen = maxLens->maxNameLen;
    short int maxRoleLen = maxLens->maxRoleLen;
    short int maxSalLen = maxLens->maxSalLen;
    short int maxDobLen = maxLens->maxDobLen;
    short int maxPosLen = maxLens->maxPosLen;

    int listEmpty = (
        (maxNameLen + maxRoleLen + maxSalLen) == 0
    );
    if (listEmpty) { return MAXLENS_LIST_EMPTY; }

    short int nameLabelLen = strlen(NAME_LABEL);
    short int roleLabelLen = strlen(ROLE_LABEL);
    short int salLabelLen = strlen(SAL_LABEL);
    short int dobLabelLen = strlen(DOB_LABEL);
    short int posLabelLen = strlen(POS_LABEL);

    maxLens->maxNameLen = (maxNameLen > nameLabelLen) ? maxNameLen : nameLabelLen;
    maxLens->maxRoleLen = (maxRoleLen > roleLabelLen) ? maxRoleLen : roleLabelLen;
    maxLens->maxSalLen = (maxSalLen > salLabelLen) ? maxSalLen : salLabelLen;
    maxLens->maxDobLen = (maxDobLen > dobLabelLen) ? maxDobLen : dobLabelLen;
    maxLens->maxPosLen = (maxPosLen > posLabelLen) ? maxPosLen : posLabelLen;

    return MAXLENS_REGULAR;
}

short int getMaxLineLen(maxLenObj* maxLens) {
    if (maxLens == NULL) { return 0; }

    short int extraSpace = MARGIN_LEN + VERTICAL_DIVIDER_LEN + MARGIN_LEN;
    short int result;

    if (maxLens->maxPosLen > 0) {
        result = (
            maxLens->maxPosLen + extraSpace +
            maxLens->maxNameLen + extraSpace +
            maxLens->maxRoleLen + extraSpace +
            maxLens->maxDobLen + extraSpace +
            maxLens->maxSalLen - 1
        );
    } else {
        result = (
            maxLens->maxNameLen + extraSpace +
            maxLens->maxRoleLen + extraSpace +
            maxLens->maxDobLen + extraSpace +
            maxLens->maxSalLen - 1
        );
    }

    return result;
}

void printTableHeader(maxLenObj* maxLens) {
    if (maxLens->maxPosLen > 0) {
        printf(
            "%-*s | %-*s | %-*s | %-*s | %-*s\n",
            maxLens->maxPosLen, POS_LABEL,
            maxLens->maxNameLen, NAME_LABEL,
            maxLens->maxRoleLen, ROLE_LABEL,
            maxLens->maxDobLen, DOB_LABEL,
            maxLens->maxSalLen, SAL_LABEL
        );
    } else {
        printf(
            "%-*s | %-*s | %-*s | %-*s\n",
            maxLens->maxNameLen, NAME_LABEL,
            maxLens->maxRoleLen, ROLE_LABEL,
            maxLens->maxDobLen, DOB_LABEL,
            maxLens->maxSalLen, SAL_LABEL
        );
    }
}

void printUnsortedChefList(chefObj ** chefList, int listLen, int enablePager) {
    if (chefList == NULL || listLen <= 0) {
        printf("Encountered an error while trying to display chef list.\n");
        printf("Please try again.\n");
        return;
    }

    short int maxNameLen, maxRoleLen, maxSalLen, maxDobLen, maxPosLen;

    maxLenObj* maxLens = getPropertiesMaxLen(chefList, listLen);
    int maxLensResult = handleMaxLens(maxLens, listLen);

    if (maxLensResult == MAXLENS_LIST_EMPTY) {
        printf("The list is empty ...\n");
        free(maxLens);
        return;
    }

    maxNameLen = maxLens->maxNameLen;
    maxRoleLen = maxLens->maxRoleLen;
    maxSalLen = maxLens->maxSalLen;
    maxDobLen = maxLens->maxDobLen;
    maxPosLen = maxLens->maxPosLen;

    short int maxLineLen = getMaxLineLen(maxLens);

    printTableHeader(maxLens);
    printHorizontalDivider("-", maxLineLen);

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char* name = getName(chefList[i]);
        char* role = getRole(chefList[i]);
        char* dob = getDateOfBirth(chefList[i]);
        long sal = getSalary(chefList[i]);
        int pos = i + 1;

        printf(
            "%0*d | %-*s | %-*s | %*s | %*ld\n",
            maxPosLen, pos,
            maxNameLen, name,
            maxRoleLen, role,
            maxDobLen, dob,
            maxSalLen, sal
        );

        if (enablePager && pos % DEFAULT_PAGE_SIZE == 0) {
            printf("\nPress <ENTER> to continue or type 'q' to exit the pager: ");

            char choice = lower(getchar());
            if (choice == 'q') {
                flushBuffer();
                break;
            }
            else if (choice != '\n') { flushBuffer(); }

            printf("\n");

            printTableHeader(maxLens);
            printHorizontalDivider("-", maxLineLen);
        }
    }

    free(maxLens);
}

void printSortedChefList(
    chefObj ** chefList,
    int listLen,
    int enablePager,
    char sortKey
) {
    if (chefList == NULL || listLen <= 0) {
        printf("Encountered an error while trying to display chef list.\n");
        printf("Please try again.\n");
        return;
    }

    chefObj ** workList = NULL;

    switch (sortKey) {
        case KEY_NAME:
            workList = orderByName(chefList, listLen);
            break;
        case KEY_SALARY:
            workList = orderBySalary(chefList, listLen);
            break;
        default:
            workList = chefList;
    }

    if (workList == NULL) {
        printf("Encountered an error while trying to display chef list.\n");
        printf("Please try again.\n");
        return;
    }

    short int maxNameLen, maxRoleLen, maxSalLen, maxDobLen;

    maxLenObj* maxLens = getPropertiesMaxLen(workList, listLen);
    int maxLensResult = handleMaxLens(maxLens, listLen);

    if (maxLensResult == MAXLENS_LIST_EMPTY) {
        printf("The list is empty ...\n");
        free(maxLens);
        return;
    }

    maxNameLen = maxLens->maxNameLen;
    maxRoleLen = maxLens->maxRoleLen;
    maxSalLen = maxLens->maxSalLen;
    maxDobLen = maxLens->maxDobLen;
    maxLens->maxPosLen = 0;

    short int maxLineLen = getMaxLineLen(maxLens);

    printTableHeader(maxLens);
    printHorizontalDivider("-", maxLineLen);

    int i;
    for (i = 0; i < listLen; i++) {
        if (workList[i] == NULL) { continue; }

        char* name = getName(workList[i]);
        char* role = getRole(workList[i]);
        char* dob = getDateOfBirth(workList[i]);
        long sal = getSalary(workList[i]);

        printf(
            "%-*s | %-*s | %*s | %*ld\n",
            maxNameLen, name,
            maxRoleLen, role,
            maxDobLen, dob,
            maxSalLen, sal
        );

        if (enablePager && (i % DEFAULT_PAGE_SIZE == 0 && i > 0)) {
            printf("\nPress <ENTER> to continue or type 'q' to exit the pager: ");

            char choice = lower(getchar());
            if (choice == 'q') {
                flushBuffer();
                break;
            }
            else if (choice != '\n') { flushBuffer(); }

            printf("\n");

            printTableHeader(maxLens);
            printHorizontalDivider("-", maxLineLen);
        }
    }

    if (workList != chefList) { free(workList); }
    free(maxLens);
}

void pressEnterTo(const char* prompt) {
    printf("\nPress <Enter> to %s: ", prompt);
    getchar();
}

void printTitleCard(void) {
    printf("--------------------------------------------\n");
    printf("***** MASTERCHEFS MANAGEMENT SOFTWARE ******\n");
    printf("--------------------------------------------\n\n");
}

void printDisplaySubmenu(const char* prompt) {
    printf("1) Display actual chef list\n");
    printf("2) Display chef list alphabetically\n");
    printf("3) Display chef list based on salary\n");
    printf("0) Return to main menu\n\n");
    printf("%s", prompt);
}

void printEditChefSubmenu(const char* prompt) {
    printf("1) Edit the name of the chef\n");
    printf("2) Edit the role of the chef\n");
    printf("3) Edit the date of birth of the chef\n");
    printf("4) Edit the salary of the chef\n");
    printf("5) Edit another chef\n");
    printf("0) Return to main menu\n\n");
    printf("%s", prompt);
}

void printEditListSubmenu(const char* prompt) {
    printf("1) Add a new chef to the list\n");
    printf("2) Edit the profile of a particular chef\n");
    printf("3) Remove a particular chef\n");
    printf("0) Return to main menu\n\n");
    printf("%s", prompt);
}

void printSearchSubmenu(const char* prompt) {
    printf("1) Search for chefs by name\n");
    printf("2) Search for chefs by salary range\n");
    printf("0) Return to main menu\n\n");
    printf("%s", prompt);
}

void printMainMenu(const char* prompt) {
    printf("1) Display the list of chefs\n");
    printf("2) Search for specific chefs\n");
    printf("3) Edit the list of chefs\n");
    printf("4) Calculate the total salary of all chefs\n");
    printf("5) Save the current chef list\n");
    printf("0) Exit\n\n");
    printf("%s", prompt);
}
