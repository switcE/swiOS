#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void* memset(void* dest, int value, size_t len);
void* memcpy(void* dest, const void* src, size_t len);
void* memmove(void* dest, const void* src, size_t len);
int memcmp(const void* ptr1, const void* ptr2, size_t len);

#endif // MEMORY_H