#include <drivers/vga/tty.h>
#include <drivers/x86/idt.h>
#include <core/init.h>
#include <std/stdio.h>

void main() {
    vga_clear();
    
    init_drivers();

    printf("Started!\n");

    while (1);
}