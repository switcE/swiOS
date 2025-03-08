#include "lib.h"

void *kmemcpy(void *dest, const void *src, unsigned int n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (unsigned int i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *kmemset(void *dest, int val, unsigned int n) {
    unsigned char *d = (unsigned char *)dest;
    for (unsigned int i = 0; i < n; i++) {
        d[i] = (unsigned char)val;
    }
    return dest;
}
