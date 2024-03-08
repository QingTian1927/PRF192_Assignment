/**
 * @file graphics.h
 * @author QingTian
 * @brief header file for graphics.c
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

#endif
