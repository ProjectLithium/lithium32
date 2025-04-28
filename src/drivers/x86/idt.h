#pragma once
#include <stdint.h>

#define IDT_FLAG_GATE_TASK              0x5
#define IDT_FLAG_GATE_16BIT_INT         0x6
#define IDT_FLAG_GATE_16BIT_TRAP        0x7
#define IDT_FLAG_GATE_32BIT_INT         0xE
#define IDT_FLAG_GATE_32BIT_TRAP        0xF

#define IDT_FLAG_RING0          (0 << 5)
#define IDT_FLAG_RING1          (1 << 5)
#define IDT_FLAG_RING2          (2 << 5)
#define IDT_FLAG_RING3          (3 << 5)

#define IDT_FLAG_PRESENT        0x80

void idt_install();