/**
 * @file database.c
 * @author QingTian
 * @brief functions related to reading and writing to ".chefs" files
 *
 * Line format:
 *
 *   NAME:CHEF NAME,ROLE:CHEF ROLE,DOB:YYYY/MM/DD,SAL:1000000000\n
 *
 * Terminologies:
 *
 *   *) Property: a unique field of information about a particular chef
 *                (e.g: name, role, date of birth, salary)
 *
 *   *) Identifier: the value of a specific field of information about a
 *                  particular chef (though this name is rather misleading)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

const int MAX_LINE_LEN = (
    NAME_IDENTIFIER_LEN + MAX_NAME_LEN + SEPARATOR_LEN +
    ROLE_IDENTIFIER_LEN + MAX_ROLE_LEN + SEPARATOR_LEN +
    DOB_IDENTIFIER_LEN  + MAX_DATE_LEN + SEPARATOR_LEN +
    SAL_IDENTIFIER_LEN + MAX_SALARY_LEN + NEWLINE_LEN +
    NULL_TERMINATOR_LEN
);

const char* IDENTIFIERS_TABLE[] = {"NAME", "ROLE", "DOB", "SAL"};
const int IDENTIFIERS_TABLE_LEN = sizeof(IDENTIFIERS_TABLE) / sizeof(IDENTIFIERS_TABLE[0]);

const char FLAGS_TABLE[] = {'n', 'r', 'd', 's'};
const int FLAGS_TABLE_LEN = sizeof(FLAGS_TABLE) / sizeof(FLAGS_TABLE[0]);

int doesFileExist(const char* fileName) {
    FILE* filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        return 0;
    }
    return 1;
}

long convertSalary(const char* str) {
    if (str == NULL) { return -1; }

    long num;
    int result = sscanf(str, "%ld", &num);

    if (result != 1) { return - 1; }
    return num;
}

char determineIdentifier(const char* identifier) {
    if (identifier == NULL) { return 0; }

    int i;
    for (i = 0; i < IDENTIFIERS_TABLE_LEN; i++) {
        int isMatchingIdentifier = (
            strncmp(identifier, IDENTIFIERS_TABLE[i], MAX_IDENTIFIER_LEN) == 0
        );

        if (isMatchingIdentifier) {
            char flag = FLAGS_TABLE[i];
            return flag;
        }
    }
    return 0;
}

chefObj* parseChefLine(char* line) {
    if (line == NULL) { return NULL; }

    chefObj* chefPtr = newChef();
    if (chefPtr == NULL) { return NULL; }

    char* property;
    char* propertySavePtr;
    char* identifierSavePtr;

    property = strtok_r(line, PROPERTY_SEPARATOR, &propertySavePtr);

    while (property != NULL) {
        int propertyLen = strlen(property);
        if (property[propertyLen - 1] == '\n') {
            property[propertyLen - 1] = '\0';
        }

        char* identifier = strtok_r(
            property, IDENTIFIER_SEPARATOR, &identifierSavePtr
        );

        char identifierFlag = 0;
        while (identifier != NULL) {

            if (identifierFlag == 0) {
                identifierFlag = determineIdentifier(identifier);

                identifier = strtok_r(
                    NULL, IDENTIFIER_SEPARATOR, &identifierSavePtr
                );

                continue;
            }

            int result;
            switch (identifierFlag) {
                case NAME_IDENTIFIER_FLAG:
                    result = setName(chefPtr, identifier);
                    break;
                case ROLE_IDENTIFIER_FLAG:
                    result = setRole(chefPtr, identifier);
                    break;
                case DOB_IDENTIFIER_FLAG:
                    result = setDateOfBirth(chefPtr, identifier);
                    break;
                case SAL_IDENTIFIER_FLAG:
                    result = setSalary(chefPtr, convertSalary(identifier));
                    break;
                default:
                    result = SET_PROPERTY_FAIL;
            }

            if (result == SET_PROPERTY_FAIL) {
                free(chefPtr);
                return NULL;
            }
            identifierFlag = 0;
        }
        property = strtok_r(NULL, PROPERTY_SEPARATOR, &propertySavePtr);
    }

    return chefPtr;
}

chefObj ** readChefsFile(const char* fileName) {
    int fileDoesNotExist = doesFileExist(fileName) == 0;
    if (fileDoesNotExist) { return NULL; }

    FILE* file = fopen(fileName, "r");
    if (file == NULL) { return NULL; }

    char line[MAX_LINE_LEN];

    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        chefObj* parsedChef = parseChefLine(line);

        if (parsedChef == NULL) { continue; }
        printf(
            "%s - %s - %s - %ld\n",
            getName(parsedChef),
            getRole(parsedChef),
            getDateOfBirth(parsedChef),
            getSalary(parsedChef)
        );
    }
    return NULL;
}
