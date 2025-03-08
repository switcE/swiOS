#ifndef LIB_H
#define LIB_H

#include <stddef.h>

size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char* src);
int strcmp(const char* str1, const char* str2);

#endif // LIB_H