#pragma once
#include <stdint.h>

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, kernel_esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp, ss;
} __attribute__((packed)) regdump;

typedef void (*isr_handler)(regdump* regs);

void x86_isr_init_gates();
void isr_install();
void isr_register_handler(int interrupt, isr_handler handler);