#ifndef _USERINPUT_H_
#define _USERINPUT_H_

#include <stddef.h>

void flushBuffer(void);

int getIntInput(void);
double getDoubleInput(void);

size_t getStringInput(char* strPtr, int maxLen);

#endif
