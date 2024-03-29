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

    // fclose(NULL) could be problematic.
    if (filePtr == NULL) { return FILE_NOTFOUND; }

    fclose(filePtr);
    return FILE_EXISTS;
}

int writeChefsFile (const char* fileName, chefObj ** chefList, int listLen) {
    if (fileName == NULL || chefList == NULL || listLen <= 0) {
        return WRITE_FILE_FAIL;
    }

    FILE* file = fopen(fileName, "w");
    if (file == NULL) { return WRITE_FILE_FAIL; }

    /* FOCUS */
    int i;
    for (i = 0; i < listLen; i++) {
        chefObj* chef = chefList[i];
        if (chef == NULL) { continue; }

        char* name = getName(chef);
        char* role = getRole(chef);
        char* dob = getDateOfBirth(chef);
        long sal = getSalary(chef);

        fprintf(
            file,
            "NAME:%s,ROLE:%s,DOB:%s,SAL:%ld\n",
            name, role, dob, sal
        );
    }
    /* FOCUS */

    fclose(file);
    return WRITE_FILE_OKAY;
}

int setFileProperties(chefFileObj* readFile, int listLen, chefObj ** chefList) {
    if (readFile == NULL || listLen <= 0 || chefList == NULL) {
        return SET_PROPERTY_FAIL;
    }

    readFile->listLen = listLen;
    readFile->chefList = chefList;

    return SET_PROPERTY_OKAY;
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

int interpretIdentifierFlag(chefObj* chefPtr, char* identifier, const char identifierFlag) {
    switch (identifierFlag) {
        case NAME_IDENTIFIER_FLAG:
            return setName(chefPtr, identifier);
        case ROLE_IDENTIFIER_FLAG:
            return setRole(chefPtr, identifier);
        case DOB_IDENTIFIER_FLAG:
            return setDateOfBirth(chefPtr, identifier);
        case SAL_IDENTIFIER_FLAG:
            return setSalary(chefPtr, convertSalary(identifier));
        default:
            return SET_PROPERTY_FAIL;
    }
}

/* FOCUS */
int parseChefProperty(char* property, chefObj* chefPtr) {
    if (property == NULL || chefPtr == NULL) { return SET_PROPERTY_FAIL; }

    char* identifierSavePtr;
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
        int result = interpretIdentifierFlag(chefPtr, identifier, identifierFlag);
        if (result == SET_PROPERTY_FAIL) { return SET_PROPERTY_FAIL; }

        identifierFlag = 0;
    }
    return SET_PROPERTY_OKAY;
}
/* FOCUS */

chefObj* parseChefLine(char* line) {
    if (line == NULL) { return NULL; }

    chefObj* chefPtr = newChef();
    if (chefPtr == NULL) { return NULL; }

    char* property;
    char* propertySavePtr;

    /* FOCUS */
    property = strtok_r(line, PROPERTY_SEPARATOR, &propertySavePtr);

    while (property != NULL) {
        int propertyLen = strlen(property);
        if (property[propertyLen - 1] == '\n') {
            property[propertyLen - 1] = '\0';
        }

        int parsingResult = parseChefProperty(property, chefPtr);
        if (parsingResult == SET_PROPERTY_FAIL) {
            free(chefPtr);
            return NULL;
        }

        property = strtok_r(NULL, PROPERTY_SEPARATOR, &propertySavePtr);
    }
    /* FOCUS */

    return chefPtr;
}

chefFileObj* readChefsFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) { return NULL; }

    char line[MAX_LINE_LEN];

    chefObj ** chefList = newChefList(MAX_CHEFS);
    if (chefList == NULL) {
        fclose(file);
        return NULL;
    }

    /* FOCUS */
    int chefCount = 0;
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        if (chefCount > MAX_CHEFS) { break; }

        int isEmptyLine = line[0] == '\n';
        if (isEmptyLine) { continue; }

        chefObj* parsedChef = parseChefLine(line);
        if (parsedChef == NULL) { continue; }

        chefList[chefCount] = parsedChef;
        chefCount++;
    }
    fclose(file);
    /* FOCUS */

    if (chefCount <= 0) {
        free(chefList);
        return NULL;
    }

    chefFileObj* readFile = malloc(sizeof(chefFileObj));
    if (readFile == NULL) {
        free(chefList);
        return NULL;
    }

    if (chefCount == MAX_CHEFS) {
        setFileProperties(readFile, MAX_CHEFS, chefList);
        return readFile;
    }

    chefObj ** resizedList = resizeChefList(chefList, MAX_CHEFS, chefCount);
    if (resizedList == NULL) {
        setFileProperties(readFile, MAX_CHEFS, chefList);
        return readFile;
    }

    chefList = resizedList;
    setFileProperties(readFile, chefCount, chefList);

    return readFile;
}
