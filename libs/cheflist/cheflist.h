/**
 * @file cheflist.h
 * @author QingTian
 * @brief header file for cheflist.c
 */

#ifndef _CHEFLIST_H_
#define _CHEFLIST_H_

#include "../chefobject/chefobject.h"

#define MAX_CHEFS 100
#define DEFAULT_CHEFLIST_SIZE 10

#define APPEND_CHEF_FAIL -1
#define APPEND_CHEF_FULL 0
#define APPEND_CHEF_OKAY 1

#define CHEFLIST_ERRO -2
#define CHEFLIST_FULL -1

int initializeChefList(chefObj** chefList, int listLen);

chefObj ** newChefList(int listLen);
chefObj* newChef(void);

int checkChefListStatus(chefObj ** chefList, int listLen);
int appendChefToList(chefObj ** chefList, int listLen, chefObj* chefPtr);
chefObj ** appendChefToFullList(chefObj ** chefList, int* listLenPtr, chefObj* chefPtr);

chefObj ** searchChefByName(
    chefObj ** chefList,
    int listLen,
    char* nameQuery
);
chefObj ** searchChefBySalaryRange(
    chefObj ** chefList,
    int listLen,
    long minSalary,
    long maxSalary
);

long long calculateChefTotalSalary(chefObj ** chefList, int listLen);

#endif