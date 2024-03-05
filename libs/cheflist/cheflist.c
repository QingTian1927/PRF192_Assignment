#include <stdlib.h>
#include "../chefobject/chefobject.h"

#define MAX_CHEFS 100
#define DEFAULT_CHEFLIST_SIZE 10

int initializeChefList(struct chefObj** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return 0; }

    int i;
    for (i = 0; i < listLen; i++) {
        chefList[i] = NULL;
    }
    return 1;
}

struct chefObj** newChefList(int listLen) {
    if (listLen <= 0) { return NULL; }

    int pointerSize = sizeof(struct chefObj*);
    struct chefObj** chefList = calloc(listLen, pointerSize);
    if (chefList == NULL) { return NULL; }

    initializeChefList(chefList, listLen);
    return chefList;
}

struct chefObj* newChef(void) {
    struct chefObj* newChef = calloc(1, sizeof(struct chefObj));
    if (newChef == NULL) { return NULL; }

    return newChef;
}
