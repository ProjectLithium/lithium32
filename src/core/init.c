#include "init.h"
#include <drivers/x86/gdt.h>
#include <drivers/x86/idt.h>
#include <drivers/x86/isr.h>
#include <drivers/devices/irq.h>
#include <drivers/devices/time/pit.h>
#include <drivers/devices/keyboard/keyboard.h>

void init_drivers()
{
    gdt_install();
    idt_install();
    isr_install();
    irq_install();

    // hardware part
    pit_init();
    keyboard_init();
    return;
}