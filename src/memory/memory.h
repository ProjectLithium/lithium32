#pragma once
#include <stddef.h>

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* ptr, int value, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);