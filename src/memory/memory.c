#include "memory.h"

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;

    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }

    return ptr;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    const unsigned char* a = (const unsigned char*)ptr1;
    const unsigned char* b = (const unsigned char*)ptr2;

    for (size_t i = 0; i < num; i++) {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return 0;
}