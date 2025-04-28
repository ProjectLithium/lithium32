#include "init.h"
#include <drivers/x86/gdt.h>
#include <drivers/x86/idt.h>
#include <drivers/x86/isr.h>

void init_drivers()
{
    gdt_install();
    idt_install();
    isr_install();
    return;
}