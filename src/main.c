#include <drivers/vga/tty.h>
#include <drivers/x86/isr.h>
#include <drivers/devices/irq.h>
#include <drivers/devices/keyboard/keyboard.h>
#include <drivers/io/io.h>
#include <core/init.h>
#include <std/stdio.h>

void timer_handler(regdump* regs)
{
    // printf("."); do nothing, i hate this timer
}

void main() {
    vga_clear();
    tty_init();
    
    init_drivers();

    irq_register_handler(0, timer_handler);
    keyboard_init();

    printf("Welcome to LithiumOS!\nEnter text: ");
    char* text = scan();
    printf("Text: %s", text);

    while (1);
}