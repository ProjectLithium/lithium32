#pragma once
#include <stddef.h>
#include <stdint.h>

char** split(char* str);
char* join(char** array, char symbol);
char* int_to_string(size_t num);
char* str_join(const char* a, const char* b);