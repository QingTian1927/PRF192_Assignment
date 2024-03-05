#ifndef _CHEFOBJECT_H_
#define _CHEFOBJECT_H_

// Not including null terminator
#define MAX_NAME_LEN 30
#define MAX_DATE_LEN 10
#define MAX_ROLE_LEN 20

#define SET_PROPERTY_FAIL 0
#define SET_PROPERTY_OKAY 1

struct chefObj {
    char name[MAX_NAME_LEN];
    char role[MAX_ROLE_LEN];
    char dateOfBirth[MAX_DATE_LEN];
    long salary;
};

int setName(struct chefObj* chefPtr, char* namePtr);
int setRole(struct chefObj* chefPtr, char* rolePtr);
int setSalary(struct chefObj* chefPtr, long salary);
int setDateOfBirth(struct chefObj* chefPtr, char* dateOfBirth);

char* getName(struct chefObj* chef);
char* getRole(struct chefObj* chef);
char* getDateOfBirth(struct chefObj* chef);
long getSalary(struct chefObj* chef);

#endif
