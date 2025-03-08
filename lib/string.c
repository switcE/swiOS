#include "lib.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* strcpy(char* dest, const char* src) {
    char* dest_ptr = dest;
    while ((*dest_ptr++ = *src++) != '\0');
    return dest;
}

char* strcat(char* dest, const char* src) {
    char* dest_ptr = dest;
    while (*dest_ptr != '\0') {
        dest_ptr++;
    }
    while ((*dest_ptr++ = *src++) != '\0');
    return dest;
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}