/**
 * @file stringformat.h
 * @author QingTian
 * @brief header file for stringformat.c
 */

#ifndef _STRINGFORMAT_H_
#define _STRINGFORMAT_H_

char upper(char ch);
char lower(char ch);

int isWhiteSpace(char ch);

void capitalizeString(char* str, int len);

int trimLeft(char* str, int len);
int trimRight(char* str, int len);
int trimInner(char* str, int len);
int fullTrim(char* str, int len);

#endif
