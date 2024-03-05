/**
 * @file chefobject.c
 * @author QingTian
 * @brief functions related to managing chefs' data structure
 */

#include <string.h>

#include "chefobject.h"
#include "../dateparser/dateparser.h"
#include "../stringformat/stringformat.h"

const char* ROLES_TABLE[] = {
    "APPRENTICE COOK",
    "JUNIOR CHEF",
    "SEASONED CHEF",
    "MASTER CHEF"
};
const int ROLES_TABLE_LEN = sizeof(ROLES_TABLE) / sizeof(ROLES_TABLE[0]);

int isInvalidString(char* str, int expectedLen) {
    int strLen = strlen(str);
    int result = strLen <= 0 || strLen >= expectedLen;
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

int setName(struct chefObj* chefPtr, char* namePtr) {
    if (chefPtr == NULL || namePtr == NULL) { return SET_PROPERTY_FAIL; }

    if (isInvalidString(namePtr, MAX_NAME_LEN)) { return SET_PROPERTY_FAIL; }

    formatName(namePtr);
    strncpy(chefPtr->name, namePtr, MAX_NAME_LEN);

    return SET_PROPERTY_OKAY;
}

int setRole(struct chefObj* chefPtr, char* rolePtr) {
    if (chefPtr == NULL || rolePtr == NULL) {
        return SET_PROPERTY_FAIL;
    }

    if (isInvalidString(rolePtr, MAX_ROLE_LEN)) {
        return SET_PROPERTY_FAIL;
    }

    if (!isValidRole(rolePtr)) { return SET_PROPERTY_FAIL; }

    strncpy(chefPtr->role, rolePtr, MAX_ROLE_LEN);

    return SET_PROPERTY_OKAY;
}

int setSalary(struct chefObj* chefPtr, long salary) {
    if (chefPtr == NULL || salary < 0) { return SET_PROPERTY_FAIL; }

    chefPtr->salary = salary;
    return SET_PROPERTY_OKAY;
}

int setDateOfBirth(struct chefObj* chefPtr, char* dateOfBirth) {
    if (chefPtr == NULL || dateOfBirth == NULL) { return SET_PROPERTY_FAIL; }

    if (!isValidDateString(dateOfBirth)) {
        return SET_PROPERTY_FAIL;
    }

    strncpy(chefPtr->dateOfBirth, dateOfBirth, MAX_DATE_LEN);

    return SET_PROPERTY_OKAY;
}


char* getName(struct chefObj chef) {
    char* name = chef.name;
    return name;
}

char* getRole(struct chefObj chef) {
    char* role = chef.role;
    return role;
}

char* getDateOfBirth(struct chefObj chef) {
    char* dateOfBirth = chef.dateOfBirth;
    return dateOfBirth;
}

long getSalary(struct chefObj chef) {
    long salary = chef.salary;
    return salary;
}
