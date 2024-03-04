/**
 * @file chefobject.c
 * @author QingTian
 * @brief functions related to managing chefs' data structure
 */

#include <string.h>

#include "chefobject.h"
#include "../dateparser/dateparser.h"

int isInvalidString(char* str, int expectedLen) {
    int strLen = strlen(str);
    int result = strLen <= 0 || strLen >= expectedLen;
    return result;
}

int setName(struct chefObj* chefPtr, char* namePtr) {
    if (chefPtr == NULL || namePtr == NULL) { return SET_PROPERTY_FAIL; }

    if (isInvalidString(namePtr, MAX_NAME_LEN)) { return SET_PROPERTY_FAIL; }

    chefPtr->name = namePtr;
    return SET_PROPERTY_OKAY;
}

int setSpecialization(struct chefObj* chefPtr, char* rolePtr) {
    if (chefPtr == NULL || rolePtr == NULL) {
        return SET_PROPERTY_FAIL;
    }

    if (isInvalidString(rolePtr, MAX_ROLE_LEN)) {
        return SET_PROPERTY_FAIL;
    }

    chefPtr->role = rolePtr;
    return SET_PROPERTY_OKAY;
}

int setSalary(struct chefObj* chefPtr, long salary) {
    if (chefPtr == NULL || salary < 0) { return SET_PROPERTY_FAIL; }

    chefPtr->salary = salary;
    return SET_PROPERTY_OKAY;
}

int setDateOfBirth(struct chefObj* chefPtr, char* dateOfBirth) {
    if (chefPtr == NULL || dateOfBirth == NULL) { return SET_PROPERTY_FAIL; }

    if (!isValidDate(dateOfBirth, strlen(dateOfBirth))) {
        return SET_PROPERTY_FAIL;
    }

    chefPtr->dateOfBirth = dateOfBirth;
    return SET_PROPERTY_OKAY;
}


char* getName(struct chefObj chef) {
    char* name = chef.name;
    return name;
}

char* getSpecialization(struct chefObj chef) {
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
