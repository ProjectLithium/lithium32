#include "keyboard.h"
#include <drivers/devices/irq.h>
#include <drivers/io/io.h>
#include <std/stdio.h>
#include <std/string.h>
#include <stdbool.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define PS2_KEYCODE_PORT 0x60

int keycode = -1;

void keyboard_handler(regdump* regs)
{
    uint8_t scancode = x86_inb(PS2_KEYCODE_PORT);

    if (scancode & 0x80)
    {
        keycode = -1;
        return;
    }

    if (scancode > 57) return;
    keycode = scancode;
}

int keyboard_get_key()
{
    return keycode;
}

void keyboard_init()
{
    irq_register_handler(1, keyboard_handler);
}
