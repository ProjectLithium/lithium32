#include <drivers/vga/tty.h>
#include <drivers/x86/isr.h>
#include <drivers/devices/irq.h>
#include <drivers/io/io.h>
#include <core/init.h>
#include <std/stdio.h>
#include <shell/shell.h>
#include <boot/multiboot.h>
#include <memory/detection.h>

void main(uint32_t magic, multiboot_info_t* mb_info) {
    vga_clear();
    tty_init();

    printf("Multiboot Magic: 0x%x\n", magic);

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Use a Multiboot-compliant bootloader!\n");
        return;
    }

    if (!(mb_info->flags & (1 << 6))) {
        printf("Memory map is not available using this boot protocol!\n");
        return;
    }

    printf("Initializing system...\n");

    init_drivers();
    init_memory_detector(mb_info);
    printf("Avaliable memory: %d MB\n", memory_get_ram_size() / 1000 / 1000);


    printf("Welcome to LithiumOS!\n");
    shell_run();

    while (1);
}
