#include <stdlib.h>
#include <string.h>
#include "../chefobject/chefobject.h"

#define MAX_CHEFS 100
#define DEFAULT_CHEFLIST_SIZE 10

#define APPEND_CHEF_FAIL -1
#define APPEND_CHEF_FULL 0
#define APPEND_CHEF_OKAY 1

#define CHEFLIST_ERRO -2
#define CHEFLIST_FULL -1

int initializeChefList(chefObj** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return 0; }

    int i;
    for (i = 0; i < listLen; i++) {
        chefList[i] = NULL;
    }
    return 1;
}

// Returns an array of pointers to struct
chefObj ** newChefList(int listLen) {
    if (listLen <= 0 || listLen > MAX_CHEFS) { return NULL; }

    int pointerSize = sizeof(chefObj*);
    chefObj** chefList = calloc(listLen, pointerSize);
    if (chefList == NULL) { return NULL; }

    initializeChefList(chefList, listLen);
    return chefList;
}

chefObj* newChef(void) {
    chefObj* newChef = calloc(1, sizeof(chefObj));
    if (newChef == NULL) { return NULL; }

    return newChef;
}

chefObj ** appendChefToFullList(
    chefObj ** chefList,
    int* listLenPtr,
    chefObj* chefPtr
) {
    int listLen = *listLenPtr;
    if (chefList == NULL || chefPtr == NULL) { return NULL; }

    int newLen = listLen + 1;
    chefObj ** resizedList = realloc(chefList, newLen * sizeof(chefObj*));
    if (resizedList == NULL) { return NULL; }

    resizedList[listLen] = chefPtr;
    *listLenPtr = newLen;

    return resizedList;
}

int checkChefListStatus(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return CHEFLIST_ERRO; }

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] != NULL) { continue; }
        return i;
    }
    return CHEFLIST_FULL;
}

int appendChefToList(chefObj ** chefList, int listLen, chefObj* chefPtr) {
    if (chefList == NULL || chefPtr == NULL || listLen <= 0) {
        return APPEND_CHEF_FAIL;
    }

    int listStatus = checkChefListStatus(chefList, listLen);
    if (listStatus == CHEFLIST_FULL) { return APPEND_CHEF_FULL; }

    chefList[listStatus] = chefPtr;
    return APPEND_CHEF_OKAY;
}

chefObj ** searchChefByName(chefObj ** chefList, int listLen, char* nameQuery) {
    int isInvalidParameter = (
        chefList == NULL || listLen <= 0 || nameQuery == NULL ||
        strlen(nameQuery) > MAX_NAME_LEN
    );
    if (isInvalidParameter) { return NULL; }

    chefObj ** searchResult = calloc(listLen, sizeof(chefObj*));
    if (searchResult == NULL) { return NULL; }
    initializeChefList(searchResult, listLen);

    int hasNoMatch = 1;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char* currentName = getName(chefList[i]);
        int isMatchingName = strncmp(currentName, nameQuery, MAX_NAME_LEN);

        if (isMatchingName != 0) { continue; }
        appendChefToList(searchResult, listLen, chefList[i]);
        hasNoMatch = 0;
    }

    if (hasNoMatch) {
        free(searchResult);
        return NULL;
    }
    return searchResult;
}

chefObj ** searchChefBySalaryRange(
    chefObj ** chefList,
    int listLen,
    long minSalary,
    long maxSalary
) {
    int isInvalidParameter = (
        chefList == NULL || listLen <= 0 || minSalary < 0 || maxSalary < 0
    );
    if (isInvalidParameter) { return NULL; }

    chefObj ** searchResult = calloc(listLen, sizeof(chefObj*));
    if (searchResult == NULL) { return NULL; }

    int hasNoMatch = 1;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        long currentSalary = getSalary(chefList[i]);
        int isMatchingSalary = minSalary >= currentSalary || currentSalary <= maxSalary;

        if (isMatchingSalary == 0) { continue; }
        appendChefToList(searchResult, listLen, chefList[i]);
        hasNoMatch = 0;
    }

    if (hasNoMatch) {
        free(searchResult);
        return NULL;
    }
    return searchResult;
}

long long calculateChefTotalSalary(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return 0; }

    long long total = 0;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        long long currentSalary = (long long) getSalary(chefList[i]);
        total += currentSalary;
    }
    return total;
}
