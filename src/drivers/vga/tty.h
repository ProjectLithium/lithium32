#pragma once
#include <stdint.h>
#include <stdbool.h>

// VGA foreground colors
#define VGA_FG_BLACK         0x00
#define VGA_FG_BLUE          0x01
#define VGA_FG_GREEN         0x02
#define VGA_FG_CYAN          0x03
#define VGA_FG_RED           0x04
#define VGA_FG_MAGENTA       0x05
#define VGA_FG_BROWN         0x06
#define VGA_FG_LIGHT_GRAY    0x07
#define VGA_FG_DARK_GRAY     0x08
#define VGA_FG_LIGHT_BLUE    0x09
#define VGA_FG_LIGHT_GREEN   0x0A
#define VGA_FG_LIGHT_CYAN    0x0B
#define VGA_FG_LIGHT_RED     0x0C
#define VGA_FG_LIGHT_MAGENTA 0x0D
#define VGA_FG_YELLOW        0x0E
#define VGA_FG_WHITE         0x0F

// VGA background colors
#define VGA_BG_BLACK         0x00
#define VGA_BG_BLUE          0x10
#define VGA_BG_GREEN         0x20
#define VGA_BG_CYAN          0x30
#define VGA_BG_RED           0x40
#define VGA_BG_MAGENTA       0x50
#define VGA_BG_BROWN         0x60
#define VGA_BG_LIGHT_GRAY    0x70

void vga_clear();
void vga_putc(char c, uint8_t x, uint8_t y, uint8_t color);
void vga_set_cursor_pos(uint8_t x, uint8_t y);