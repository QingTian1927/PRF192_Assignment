/**
 * @file cheflist.c
 * @author QingTian
 * @brief functions related to managing a list of chefs
 *
 * NOTE: a list of chefs is essentially an array of pointers to structs.
 */

#include <stdlib.h>
#include <string.h>
#include "cheflist.h"

int initializeChefList(chefObj** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return 0; }

    int i;
    for (i = 0; i < listLen; i++) {
        chefList[i] = NULL;
    }
    return 1;
}

/* FOCUS */

// Returns an array of pointers to structs
chefObj ** newChefList(int listLen) {
    if (listLen <= 0 || listLen > MAX_CHEFS) { return NULL; }

    int pointerSize = sizeof(chefObj*);
    chefObj** chefList = calloc(listLen, pointerSize);
    if (chefList == NULL) { return NULL; }

    return chefList;
}

chefObj* newChef(void) {
    chefObj* newChef = calloc(1, sizeof(chefObj));
    if (newChef == NULL) { return NULL; }

    return newChef;
}

/* FOCUS */

chefObj* copyChef(chefObj* chefPtr) {
    chefObj* copiedChef = newChef();
    if (copiedChef == NULL) { return NULL; }

    setName(copiedChef, getName(chefPtr));
    setRole(copiedChef, getRole(chefPtr));
    setDateOfBirth(copiedChef, getDateOfBirth(chefPtr));
    setSalary(copiedChef, getSalary(chefPtr));

    return copiedChef;
}

void deleteChef(chefObj ** chefPtrPtr) {
    chefObj* chefPtr = *chefPtrPtr;
    if (chefPtr == NULL || chefPtrPtr == NULL) { return; }

    free(chefPtr);
    *chefPtrPtr = NULL;
}

void freeChefList(chefObj ** chefList, int listLen) {
    if (listLen <= 0) {
        free(chefList);
        return;
    }

    int i;
    for (i = 0; i < listLen; i++) { free(chefList[i]); }
    free(chefList);
}

void shiftListLeft(
    chefObj ** chefList,
    int listLen,
    int startIndex,
    int shiftInterval
) {
    int isFailCondition = (
        chefList == NULL || listLen <= 0 ||
        startIndex < 0 || startIndex >= listLen ||
        shiftInterval <= 0
    );
    if (isFailCondition) { return; }

    int i;
    for (i = startIndex; i < listLen - shiftInterval; i++) {
        chefList[i] = chefList[i + shiftInterval];
    }

    // Set duplicates of existing chefs to NULL
    for (i = listLen - shiftInterval; i < listLen; i++) {
        chefList[i] = NULL;
    }
}

int countChefsInList(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return CHEFLIST_ERRO; }

    int count = 0;
    int i;

    for (i = 0; i < listLen; i++) {
        if (chefList[i] != NULL) { count++; }
    }
    return count;
}

/* FOCUS */
int checkChefListStatus(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return CHEFLIST_ERRO; }

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] != NULL) { continue; }
        return i;
    }
    return CHEFLIST_FULL;
}

int insertChefIntoList(chefObj ** chefList, int listLen, chefObj* chefPtr) {
    if (chefList == NULL || chefPtr == NULL || listLen <= 0) {
        return APPEND_CHEF_FAIL;
    }

    int listStatus = checkChefListStatus(chefList, listLen);
    if (listStatus == CHEFLIST_FULL) { return APPEND_CHEF_FULL; }

    chefList[listStatus] = chefPtr;
    return APPEND_CHEF_OKAY;
}
/* FOCUS */

/* FOCUS */

/**
 * @brief Calculates the total salary of a given chef list.
 * @author L. Nga
 *
 * Calculates the total salary of all chefs within a given chef list.
 *
 * @param chefList The sourced chef list.
 * @param listLen The length of the passed in chef list.
 * @return long long The total salary of all chefs within the list.
 */
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

/* FOCUS */

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

chefObj ** resizeChefList(chefObj ** chefList, int oldLen, int newLen) {
    int isInvalidParameter = (
        chefList == NULL || oldLen <= 0 || newLen <= 0
    );
    if (isInvalidParameter) { return NULL; }
    if (oldLen == newLen) { return chefList; }

    chefObj ** resizedList = realloc(chefList, newLen * sizeof(chefObj*));
    if (resizedList == NULL) { return NULL; }

    if (oldLen > newLen) { return resizedList; }

    // Initialize extended list
    int i;
    for (i = oldLen; i < newLen; i++) {
        resizedList[i] = NULL;
    }
    return resizedList;
}

chefObj ** copyChefList(chefObj ** sourcedList, int listLen) {
    if (sourcedList == NULL || listLen <= 0) { return NULL; }

    chefObj ** copiedList = newChefList(listLen);
    if (copiedList == NULL) { return NULL; }

    int i;
    for (i = 0; i < listLen; i++) {
        chefObj* originalChef = sourcedList[i];
        if (originalChef == NULL) { continue; }

        chefObj* copiedChef = newChef();
        if (copiedChef == NULL) {
            free(copiedList);
            return NULL;
        }

        setName(copiedChef, getName(originalChef));
        setRole(copiedChef, getRole(originalChef));
        setDateOfBirth(copiedChef, getDateOfBirth(originalChef));
        setSalary(copiedChef, getSalary(originalChef));

        copiedList[i] = copiedChef;
    }

    return copiedList;
}

/* FOCUS */
void swapChef(chefObj ** firstChef, chefObj ** secondChef) {
    chefObj* temp = *firstChef;
    *firstChef = *secondChef;
    *secondChef = temp;
}

chefObj ** orderByName(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return NULL; }

    chefObj ** sortedList = copyChefList(chefList, listLen);
    if (sortedList == NULL) { return NULL; }

    // Selection sort.
    int i, j;
    for (i = 0; i < listLen; i++) {
        if (sortedList[i] == NULL) { continue; }
        int minIndex = i;

        for (j = i + 1; j < listLen; j++) {
            if (sortedList[j] == NULL) { continue; }

            char* comparedName = getName(sortedList[minIndex]);
            char* currentName = getName(sortedList[j]);

            int isNotAlphabeticallySmaller = (
                strncmp(currentName, comparedName, MAX_NAME_LEN) >= 0
            );
            if (isNotAlphabeticallySmaller) { continue; }

            minIndex = j;
        }
        swapChef(&sortedList[minIndex], &sortedList[i]);
    }

    return sortedList;
}
/* FOCUS */

/**
 * @brief Sorts a given chef list according to salary.
 * @author L. Nga
 *
 * Sorts a list of chefs according to salary, in descending order. The returned
 * chef list can be safely freed since it is a copy of the original chef list.
 *
 * Currently, the functions uses the reversed selection sort algorithm to carry
 * the sorting.
 *
 * @param chefList The chef list to be sorted.
 * @param listLen The length of the passed in chef list.
 * @return chefObj** A pointer to the sorted chef list.
 */
chefObj ** orderBySalary(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return NULL; }

    chefObj ** sortedList = copyChefList(chefList, listLen);
    if (sortedList == NULL) { return NULL; }

    // Reverse selection sort.
    int i, j;
    for (i = 0; i < listLen; i++) {
        if (sortedList[i] == NULL) { continue; }
        int maxIndex = i;

        for (j = i + 1; j < listLen; j++) {
            if (sortedList[j] == NULL) { continue; }

            long comparedSalary = getSalary(sortedList[maxIndex]);
            long currentSalary = getSalary(sortedList[j]);

            if (currentSalary <= comparedSalary) { continue; }
            maxIndex = j;
        }
        swapChef(&sortedList[maxIndex], &sortedList[i]);
    }

    return sortedList;
}

int setSearchProperties(
    chefSearchResult* searchResult,
    chefObj ** chefList,
    int listLen
) {
    if (searchResult == NULL) {
        return SET_PROPERTY_FAIL;
    }

    searchResult->resultLen = listLen;
    searchResult->resultList = chefList;

    return SET_PROPERTY_OKAY;
}

chefSearchResult* processSearchResult(
    chefObj ** matchList,
    int matches,
    int queriedListLen
) {
    chefSearchResult* searchResult = calloc(1, sizeof(chefSearchResult));
    if (searchResult == NULL || matches <= 0) {
        free(matchList);
        return searchResult;
    }

    if (matches == queriedListLen) {
        setSearchProperties(searchResult, matchList, queriedListLen);
        return searchResult;
    }

    chefObj ** resizedList = resizeChefList(matchList, queriedListLen, matches);
    if (resizedList == NULL) {
        setSearchProperties(searchResult, matchList, queriedListLen);
        return searchResult;
    }

    matchList = resizedList;
    setSearchProperties(searchResult, matchList, matches);

    return searchResult;
}

/* FOCUS */
chefSearchResult* searchChefByName(chefObj ** chefList, int listLen, char* nameQuery) {
    int isInvalidParameter = (
        chefList == NULL || listLen <= 0 || nameQuery == NULL ||
        strlen(nameQuery) > MAX_NAME_LEN
    );
    if (isInvalidParameter) { return NULL; }

    chefObj ** matchList = newChefList(listLen);
    if (matchList == NULL) { return NULL; }

    lowerStr(nameQuery, strlen(nameQuery));

    int matches = 0;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char currentName[ACTUAL_MAX_NAME_LEN];
        strncpy(currentName, getName(chefList[i]), ACTUAL_MAX_NAME_LEN);
        lowerStr(currentName, strlen(currentName));

        char* matchNameResult = strstr(currentName, nameQuery);
        if (matchNameResult == NULL) { continue; }

        insertChefIntoList(matchList, listLen, chefList[i]);
        matches++;
    }

    return processSearchResult(matchList, matches, listLen);
}
/* FOCUS */

chefSearchResult* searchChefBySalaryRange(
    chefObj ** chefList,
    int listLen,
    long minSalary,
    long maxSalary
) {
    int isInvalidParameter = (
        chefList == NULL || listLen <= 0 || minSalary < 0 || maxSalary < 0
    );
    if (isInvalidParameter) { return NULL; }

    chefObj ** matchList = newChefList(listLen);
    if (matchList == NULL) { return NULL; }

    int matches = 0;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        long currentSalary = getSalary(chefList[i]);

        int isMatchingSalary = currentSalary >= minSalary && currentSalary <= maxSalary;
        if (isMatchingSalary == 0) { continue; }

        insertChefIntoList(matchList, listLen, chefList[i]);
        matches++;
    }

    return processSearchResult(matchList, matches, listLen);
}

int findChefOriginalIndex(chefObj ** chefList, int listLen, chefObj* queriedChef) {
    if (chefList == NULL || listLen <= 0 || queriedChef == NULL) {
        return -1;
    }
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == queriedChef) {
            return i;
        }
    }
    return -1;
}
