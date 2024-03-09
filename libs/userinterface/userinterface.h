/**
 * @file userinterface.h
 * @author QingTian
 * @brief header file for userinterface.c
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "../cheflist/cheflist.h"
#include "../chefobject/chefobject.h"
#include "../stringformat/stringformat.h"

#define POS_LABEL "NO"
#define NAME_LABEL "NAME"
#define ROLE_LABEL "ROLE"
#define DOB_LABEL "D.O.B"
#define SAL_LABEL "SALARY"

#define MARGIN_LEN 1
#define VERTICAL_DIVIDER_LEN 1

#define MAXLENS_ZEROES 0
#define MAXLENS_REGULAR 1

#define DISABLE_PAGER 0
#define ENABLE_PAGER 1
#define DEFAULT_PAGE_SIZE 10

#define STANDARD_PROMPT "Enter your choice: "
#define INVALID_PROMPT "Invalid option. Please try again: "

typedef struct {
    short int maxNameLen;
    short int maxRoleLen;
    short int maxSalLen;
    short int maxDobLen;
    short int maxPosLen;
} maxLenObj;

void exitOnFatalException(const char* message);
void flushBuffer(void);

int getIntInput(void);
double getDoubleInput(void);
int getStringInput(char* strPtr, int maxLen);

int handleMaxLens(maxLenObj* maxLens, int listLen);
short int getMaxLineLen(maxLenObj* maxLens);

void printHorizontalDivider(const char* ch, int maxLineLen);
void printTableHeader(maxLenObj* maxLens);

void printUnsortedChefList(chefObj ** chefList, int listLen, int enablePager);

void printTitleCard(void);
void printEditSubmenu(const char* prompt);
void printMainMenu(const char* prompt);

#endif
