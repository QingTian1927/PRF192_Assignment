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
#define MAX_ROLE_LEN 15
#define MAX_SALARY 2000000000
#define MAX_SALARY_LEN 10

#define ACTUAL_MAX_NAME_LEN 31
#define ACTUAL_MAX_DATE_LEN 11
#define ACTUAL_MAX_ROLE_LEN 16
#define ACTUAL_MAX_SALARY_LEN 11

#define SET_PROPERTY_FAIL 0
#define SET_PROPERTY_OKAY 1

/* FOCUS */
typedef struct {
    char name[ACTUAL_MAX_NAME_LEN];
    char role[ACTUAL_MAX_ROLE_LEN];
    char dateOfBirth[ACTUAL_MAX_DATE_LEN];
    long salary;
} chefObj;
/* FOCUS */

extern const char* ROLES_TABLE[];
extern const int ROLES_TABLE_LEN;

int isValidRole(char* rolePtr);

/* FOCUS */
int setName(chefObj* chefPtr, char* namePtr);
int setRole(chefObj* chefPtr, char* rolePtr);
int setSalary(chefObj* chefPtr, long salary);
int setDateOfBirth(chefObj* chefPtr, char* dateOfBirth);
/* FOCUS */

int setAll(
    chefObj* chefPtr,
    char* namePtr,
    char* rolePtr,
    char* dateOfBirth,
    long salary
);

/* FOCUS */
char* getName(chefObj* chef);
char* getRole(chefObj* chef);
char* getDateOfBirth(chefObj* chef);
long getSalary(chefObj* chef);
/* FOCUS */

#endif
