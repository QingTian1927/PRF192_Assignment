#ifndef _CHEFOBJECT_H_
#define _CHEFOBJECT_H_

#define MAX_NAME_LEN 50
#define MAX_DATE_LEN 10
#define MAX_ROLE_LEN 20

#define SET_PROPERTY_FAIL 0
#define SET_PROPERTY_OKAY 1

struct chefObj {
    char* name;
    char* role;
    char* dateOfBirth;
    long salary;
};

int setName(struct chefObj* chefPtr, char* namePtr);
int setSpecialization(struct chefObj* chefPtr, char* rolePtr);
int setSalary(struct chefObj* chefPtr, long salary);
int setDateOfBirth(struct chefObj* chefPtr, char* dateOfBirth);

char* getName(struct chefObj chef);
char* getSpecialization(struct chefObj chef);
char* getDateOfBirth(struct chefObj chef);
long getSalary(struct chefObj chef);

#endif
