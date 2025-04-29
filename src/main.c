#include <drivers/vga/tty.h>
#include <drivers/x86/isr.h>
#include <drivers/devices/irq.h>
#include <drivers/io/io.h>
#include <core/init.h>
#include <std/stdio.h>

void timer_handler(regdump* regs)
{
    // printf("."); do nothing, i hate this timer
}

void keyboard_handler(regdump* regs)
{
    printf("Key pressed or released! ");
    uint8_t scancode = x86_inb(0x60);
    printf("Scancode: %d\n", scancode);
}

void main() {
    vga_clear();
    
    init_drivers();

    irq_register_handler(0, timer_handler);
    irq_register_handler(1, keyboard_handler);

    printf("Started!\n");

    while (1);
}