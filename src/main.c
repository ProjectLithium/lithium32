#include <drivers/vga/tty.h>
#include <std/stdio.h>
#include <core/version.h>

void main() {
    vga_clear();
    print_version();
    printf("Hello, World! Here's a number: %d :D", 15);

    while (1);
}
