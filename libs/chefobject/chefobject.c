/**
 * @file chefobject.c
 * @author QingTian
 * @brief functions related to managing chefs' data structure
 */

#include <string.h>
#include "chefobject.h"

const char* ROLES_TABLE[] = {
    "APPRENTICE COOK",
    "JUNIOR CHEF",
    "SEASONED CHEF",
    "MASTER CHEF"
};
const int ROLES_TABLE_LEN = sizeof(ROLES_TABLE) / sizeof(ROLES_TABLE[0]);

int isInvalidString(char* str, int maxLen) {
    int strLen = strlen(str);
    int result = strLen <= 0 || strLen > maxLen;
    return result;
}

void formatName(char* namePtr) {
    int len = fullTrim(namePtr, strlen(namePtr));
    capitalizeString(namePtr, len);
}

int isValidRole(char* rolePtr) {
    if (rolePtr == NULL) { return 0; }

    int i;
    for (i = 0; i < ROLES_TABLE_LEN; i++) {
        if (strncmp(rolePtr, ROLES_TABLE[i], strlen(ROLES_TABLE[i])) == 0) {
            return 1;
        }
    }
    return 0;
}

int setName(chefObj* chefPtr, char* namePtr) {
    if (chefPtr == NULL || namePtr == NULL) { return SET_PROPERTY_FAIL; }

    if (isInvalidString(namePtr, MAX_NAME_LEN)) { return SET_PROPERTY_FAIL; }

    formatName(namePtr);
    strncpy(chefPtr->name, namePtr, ACTUAL_MAX_NAME_LEN);

    return SET_PROPERTY_OKAY;
}

int setRole(chefObj* chefPtr, char* rolePtr) {
    if (chefPtr == NULL || rolePtr == NULL) {
        return SET_PROPERTY_FAIL;
    }

    if (isInvalidString(rolePtr, MAX_ROLE_LEN)) {
        return SET_PROPERTY_FAIL;
    }

    if (!isValidRole(rolePtr)) { return SET_PROPERTY_FAIL; }

    strncpy(chefPtr->role, rolePtr, ACTUAL_MAX_ROLE_LEN);

    return SET_PROPERTY_OKAY;
}

int setSalary(chefObj* chefPtr, long salary) {
    int isInvalidParameter = (
        chefPtr == NULL ||
        salary < 0 || salary > MAX_SALARY
    );
    if (isInvalidParameter) { return SET_PROPERTY_FAIL; }

    chefPtr->salary = salary;
    return SET_PROPERTY_OKAY;
}

int setDateOfBirth(chefObj* chefPtr, char* dateOfBirth) {
    if (chefPtr == NULL || dateOfBirth == NULL) { return SET_PROPERTY_FAIL; }

    if (!isValidDateString(dateOfBirth)) {
        return SET_PROPERTY_FAIL;
    }

    strncpy(chefPtr->dateOfBirth, dateOfBirth, ACTUAL_MAX_DATE_LEN);

    return SET_PROPERTY_OKAY;
}

int setAll(
    chefObj* chefPtr,
    char* namePtr,
    char* rolePtr,
    char* dateOfBirth,
    long salary
) {
    int nameResult = setName(chefPtr, namePtr);
    int roleResult = setRole(chefPtr, rolePtr);
    int dobResult = setDateOfBirth(chefPtr, dateOfBirth);
    int salaryResult = setSalary(chefPtr, salary);

    int allResult = nameResult && roleResult && dobResult && salaryResult;
    return allResult;
}

char* getName(chefObj* chef) {
    if (chef == NULL) { return NULL; }

    char* name = chef->name;
    return name;
}

char* getRole(chefObj* chef) {
    if (chef == NULL) { return NULL; }

    char* role = chef->role;
    return role;
}

char* getDateOfBirth(chefObj* chef) {
    if (chef == NULL) { return NULL; }

    char* dateOfBirth = chef->dateOfBirth;
    return dateOfBirth;
}

long getSalary(chefObj* chef) {
    if (chef == NULL) { return -1; }

    long salary = chef->salary;
    return salary;
}
