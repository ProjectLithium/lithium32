#include "keyboard.h"
#include <drivers/devices/irq.h>
#include <drivers/io/io.h>
#include <std/stdio.h>
#include <std/string.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define PS2_KEYCODE_PORT 0x60

static char key_buffer[256];

#define SC_MAX 57

const char *sc_name[] = {
  "ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8",
  "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", "R",
  "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
  "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'",
  "`", "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M",
  ",", ".", "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = {
  '?', '?', '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '?', '?',
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/', '?', '?', '?', ' '
};

static void clear_buffer(char* buf) {
    for (int i = 0; i < 256; i++)
        buf[i] = 0;
}

void keyboard_handler(regdump* regs)
{
    uint8_t scancode = x86_inb(PS2_KEYCODE_PORT);
    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        putb();
    } else if (scancode == ENTER) {
        putc('\n');
        clear_buffer(key_buffer);
    } else {
        char letter = sc_ascii[scancode];
        append(key_buffer, letter);
        putc(letter);
    }
}

void keyboard_init()
{
    irq_register_handler(1, keyboard_handler);
}
