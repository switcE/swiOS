#include "memory.h"

void* memset(void* dest, int value, size_t len) {
    unsigned char* ptr = dest;
    while (len-- > 0) {
        *ptr++ = value;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t len) {
    const unsigned char* src_ptr = src;
    unsigned char* dest_ptr = dest;
    while (len-- > 0) {
        *dest_ptr++ = *src_ptr++;
    }
    return dest;
}

void* memmove(void* dest, const void* src, size_t len) {
    const unsigned char* src_ptr = src;
    unsigned char* dest_ptr = dest;
    if (dest_ptr < src_ptr) {
        while (len-- > 0) {
            *dest_ptr++ = *src_ptr++;
        }
    } else {
        src_ptr += len;
        dest_ptr += len;
        while (len-- > 0) {
            *--dest_ptr = *--src_ptr;
        }
    }
    return dest;
}

int memcmp(const void* ptr1, const void* ptr2, size_t len) {
    const unsigned char* p1 = ptr1;
    const unsigned char* p2 = ptr2;
    while (len-- > 0) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}