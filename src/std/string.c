#include "string.h"

// String functions
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    char* original_dest = dest;
    while (n-- && (*dest++ = *src++) != '\0');
    while (n-- > 0) {
        *dest++ = '\0';
    }
    return original_dest;
}

bool strcmp(const char* s1, const char* s2) {
    if (s1 == NULL || s2 == NULL) {
        return s1 == s2;
    }
    while (*s1 && *s2) {
        if (*s1++ != *s2++) {
            return false;
        }
    }
    return *s1 == *s2;
}

void backspace(char* str) {
    size_t len = strlen(str);
    if (len > 0) {
        str[len-1] = '\0';
    }
}

void append(char* str, char c) {
    size_t len = strlen(str);
    str[len] = c;
    str[len+1] = '\0';
}

char* strcat(char* dest, const char* src) {
    char* original_dest = dest;
    dest += strlen(dest);
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

char* strncat(char* dest, const char* src, size_t n) {
    char* original_dest = dest;
    dest += strlen(dest);
    while (n-- && (*dest++ = *src++) != '\0');
    *dest = '\0';
    return original_dest;
}

int strncmp(const char* s1, const char* s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

char* strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

size_t strcspn(const char* str1, const char* str2) {
    size_t len = 0;
    while (str1[len] != '\0') {
        if (strchr(str2, str1[len]) != NULL) {
            break;
        }
        len++;
    }
    return len;
}