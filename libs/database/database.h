/**
 * @file database.h
 * @author QingTian
 * @brief Header file for database.c
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "../chefobject/chefobject.h"
#include "../cheflist/cheflist.h"

#define DEFAULT_EXTENSION ".chefs"
#define WRITE_FILE_FAIL 0
#define WRITE_FILE_OKAY 1

#define FILE_NOTFOUND 0
#define FILE_EXISTS 1

#define SEPARATOR_LEN 1
#define NEWLINE_LEN 1
#define NULL_TERMINATOR_LEN 1

#define MAX_IDENTIFIER_LEN 4  // Simply the length of the longest identifier
#define NAME_IDENTIFIER_LEN 4
#define ROLE_IDENTIFIER_LEN 4
#define DOB_IDENTIFIER_LEN 3
#define SAL_IDENTIFIER_LEN 3

#define PROPERTY_SEPARATOR ","
#define IDENTIFIER_SEPARATOR ":"

#define NAME_IDENTIFIER_FLAG 'n'
#define ROLE_IDENTIFIER_FLAG 'r'
#define DOB_IDENTIFIER_FLAG 'd'
#define SAL_IDENTIFIER_FLAG 's'

typedef struct {
    int listLen;
    chefObj ** chefList;
} chefFileObj;

int doesFileExist(const char* fileName);

int writeChefsFile (const char* fileName, chefObj ** chefList, int listLen);

chefFileObj* readChefsFile(const char* fileName);

void freeChefFile(chefFileObj* chefFile);

#endif
