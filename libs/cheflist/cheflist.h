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

typedef struct {
    int resultLen;
    chefObj ** resultList;
} chefSearchResult;

int initializeChefList(chefObj** chefList, int listLen);

chefObj ** newChefList(int listLen);
chefObj* newChef(void);

int checkChefListStatus(chefObj ** chefList, int listLen);
int appendChefToList(chefObj ** chefList, int listLen, chefObj* chefPtr);

long long calculateChefTotalSalary(chefObj ** chefList, int listLen);

chefObj ** appendChefToFullList(chefObj ** chefList, int* listLenPtr, chefObj* chefPtr);
chefObj ** resizeChefList(chefObj ** chefList, int oldLen, int newLen);
chefObj ** copyChefList(chefObj ** sourcedList, int listLen);

chefObj ** orderBySalary(chefObj ** chefList, int listLen);
chefObj ** orderByName(chefObj ** chefList, int listLen);

chefSearchResult* searchChefByName(
    chefObj ** chefList,
    int listLen,
    char* nameQuery
);
chefSearchResult* searchChefBySalaryRange(
    chefObj ** chefList,
    int listLen,
    long minSalary,
    long maxSalary
);

#endif
