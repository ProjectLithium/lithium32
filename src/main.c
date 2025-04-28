#include <drivers/vga/tty.h>
#include <core/init.h>
#include <std/stdio.h>
#include <core/version.h>

void main() {
    vga_clear();
    print_version();
    printf("Loading drivers...\n");
    init_drivers();
    printf("Drivers initialized!\n");

    while (1);
}
