/**
 * @file chefobject.h
 * @author QingTian
 * @brief header file for chefobject.c
 */

#ifndef _CHEFOBJECT_H_
#define _CHEFOBJECT_H_

#include "../dateparser/dateparser.h"
#include "../stringformat/stringformat.h"

// Not including null terminator
#define MAX_NAME_LEN 30
#define MAX_DATE_LEN 10
#define MAX_ROLE_LEN 20

#define SET_PROPERTY_FAIL 0
#define SET_PROPERTY_OKAY 1

typedef struct {
    char name[MAX_NAME_LEN];
    char role[MAX_ROLE_LEN];
    char dateOfBirth[MAX_DATE_LEN];
    long salary;
} chefObj;

int isValidRole(char* rolePtr);

int setName(chefObj* chefPtr, char* namePtr);
int setRole(chefObj* chefPtr, char* rolePtr);
int setSalary(chefObj* chefPtr, long salary);
int setDateOfBirth(chefObj* chefPtr, char* dateOfBirth);

char* getName(chefObj* chef);
char* getRole(chefObj* chef);
char* getDateOfBirth(chefObj* chef);
long getSalary(chefObj* chef);

#endif
