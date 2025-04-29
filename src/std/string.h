#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// String functions
size_t strlen(const char* str);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
bool strcmp(const char* s1, const char* s2);
void backspace(char* str);
void append(char* str, char c);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);
int strncmp(const char* s1, const char* s2, size_t n);
char* strchr(const char* str, int c);
size_t strcspn(const char* str1, const char* str2);