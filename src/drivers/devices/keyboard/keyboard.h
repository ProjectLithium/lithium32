#pragma once
#include <stdbool.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

void keyboard_init();
int keyboard_get_key();