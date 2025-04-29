#pragma once
#include <drivers/x86/isr.h>

typedef void (*irq_handler)(regdump* regs);

void irq_install();
void irq_register_handler(int irq, irq_handler handler);