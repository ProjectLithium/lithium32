#pragma once
#include <stdint.h>

#define x86_GDT_CODE_SEGMENT 0x08
#define x86_GDT_DATA_SEGMENT 0x10

void gdt_install();