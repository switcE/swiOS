#ifndef LIB_H
#define LIB_H

unsigned int strlen(const char *str);
char *strcpy(char *dest, const char *src);
void *kmemcpy(void *dest, const void *src, unsigned int n);
void *kmemset(void *dest, int val, unsigned int n);

#endif
