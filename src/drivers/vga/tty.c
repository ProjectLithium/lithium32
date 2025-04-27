#include "tty.h"
#include <drivers/io/io.h>

/*
VGA notes:
    screen size is 80 columns x 25 rows
    each character is 2 bytes: 1 byte - character; 2 byte - character color
*/

void vga_clear()
{
    uint16_t *vram = (uint16_t*) 0xb8000;
    uint16_t blank = (0x07 << 8) | ' ';

    for (int i = 0; i < 80 * 25; ++i) {
        vram[i] = blank;
    }
}

void vga_putc(char c, uint8_t x, uint8_t y, uint8_t color)
{
    uint16_t *vram = (uint16_t*) 0xb8000;
    uint16_t symbol = (color << 8) | c;

    vram[y * 80 + x] = symbol;
}

void vga_set_cursor_pos(uint8_t x, uint8_t y)
{
    uint16_t pos = y * 80 + x;

    x86_outb(0x3D4, 0x0F);  // Выбираем регистр низкого байта
    x86_outb(0x3D5, (uint8_t)(pos & 0xFF));  // Записываем низкий байт

    x86_outb(0x3D4, 0x0E);  // Выбираем регистр высокого байта
    x86_outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}