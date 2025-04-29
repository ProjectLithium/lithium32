#pragma once
#include <stdbool.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

void keyboard_init();
void keyboard_clear_buffer();
bool keyboard_is_flushed();
char* keyboard_get_buffer();