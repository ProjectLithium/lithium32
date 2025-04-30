#include <drivers/vga/tty.h>
#include <drivers/x86/isr.h>
#include <drivers/devices/irq.h>
#include <drivers/devices/keyboard/keyboard.h>
#include <drivers/io/io.h>
#include <core/init.h>
#include <std/stdio.h>
#include <shell/shell.h>
#include <drivers/devices/time/pit.h>

void main() {
    vga_clear();
    tty_init();
    
    init_drivers();
    
    pit_init();
    keyboard_init();

    printf("Welcome to LithiumOS!\n");
    shell_run();

    while (1);
}