#include "stdio.h"
#include "string.h"
#include <drivers/vga/tty.h>
#include <drivers/devices/keyboard/keyboard.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

int screenX = 0, screenY = 0;
int lastLineEndX[25];

static char buffer[256];

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

void tty_init()
{
    for (int i = 0; i < 25; i++)
        lastLineEndX[i] = -1;
}


void scrollback(int lines)
{
    // Move lines up
    for (int y = 0; y < 25 - lines; y++) {
        for (int x = 0; x < 80; x++) {
            uint8_t ch = vga_getc(x, y + lines);
            vga_putc(ch, x, y, VGA_FG_LIGHT_GRAY | VGA_BG_BLACK);
        }
        lastLineEndX[y] = lastLineEndX[y + lines];  // shift lastLineEndX up too
    }

    // Clear the last `lines` lines
    for (int y = 25 - lines; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            vga_putc(' ', x, y, VGA_FG_LIGHT_GRAY | VGA_BG_BLACK);
        }
        lastLineEndX[y] = -1;
    }

    screenY = 25 - 1;  // stay on the last line
    screenX = 0;
    vga_set_cursor_pos(screenX, screenY);
}

void clear()
{
    vga_clear();
    screenX = 0;
    screenY = 0;
    vga_set_cursor_pos(screenX, screenY);
}

void putc(char c)
{
    switch (c)
    {
        case '\n':
            if (screenX > 0)
                lastLineEndX[screenY] = screenX - 1;
            else
                lastLineEndX[screenY] = -1;
            screenX = 0;
            screenY++;
            break;

        case '\t':
            for (int i = 0; i < 4 - (screenX % 4); i++)
                putc(' ');
            return;

        case '\r':
            screenX = 0;
            break;

        default:
            vga_putc(c, screenX, screenY, VGA_BG_BLACK | VGA_FG_LIGHT_GRAY);
            screenX++;
            break;
    }

    if (screenX >= 80)
    {
        lastLineEndX[screenY] = 79;
        screenY++;
        screenX = 0;
    }

    if (screenY >= 25) {
        scrollback(1);
    }

    vga_set_cursor_pos(screenX, screenY);
}

void puts(const char* str)
{
    while(*str)
        putc(*str++);
}

void putb()
{
    if (screenX > 0) {
        screenX--;
    } else if (screenY > 0) {
        screenY--;
        if (lastLineEndX[screenY] != -1)
            screenX = lastLineEndX[screenY] + 1;
        else
            screenX = 0;
    } else {
        return; // Top-left corner
    }

    vga_putc(' ', screenX, screenY, VGA_FG_LIGHT_GRAY | VGA_BG_BLACK);
    vga_set_cursor_pos(screenX, screenY);
}

const char g_HexChars[] = "0123456789abcdef";

void printf_unsigned(unsigned long long number, int radix)
{
    char buffer[32];
    int pos = 0;

    do 
    {
        unsigned long long rem = number % radix;
        number /= radix;
        buffer[pos++] = g_HexChars[rem];
    } while (number > 0);

    while (--pos >= 0)
        putc(buffer[pos]);
}

void printf_signed(long long number, int radix)
{
    if (number < 0)
    {
        putc('-');
        printf_unsigned(-number, radix);
    }
    else printf_unsigned(number, radix);
}

#define PRINTF_STATE_NORMAL         0
#define PRINTF_STATE_LENGTH         1
#define PRINTF_STATE_LENGTH_SHORT   2
#define PRINTF_STATE_LENGTH_LONG    3
#define PRINTF_STATE_SPEC           4

#define PRINTF_LENGTH_DEFAULT       0
#define PRINTF_LENGTH_SHORT_SHORT   1
#define PRINTF_LENGTH_SHORT         2
#define PRINTF_LENGTH_LONG          3
#define PRINTF_LENGTH_LONG_LONG     4

void printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int state = PRINTF_STATE_NORMAL;
    int length = PRINTF_LENGTH_DEFAULT;
    int radix = 10;
    bool sign = false;
    bool number = false;

    while (*fmt)
    {
        switch (state)
        {
            case PRINTF_STATE_NORMAL:
                switch (*fmt)
                {
                    case '%':   state = PRINTF_STATE_LENGTH;
                                break;
                    default:    putc(*fmt);
                                break;
                }
                break;

            case PRINTF_STATE_LENGTH:
                switch (*fmt)
                {
                    case 'h':   length = PRINTF_LENGTH_SHORT;
                                state = PRINTF_STATE_LENGTH_SHORT;
                                break;
                    case 'l':   length = PRINTF_LENGTH_LONG;
                                state = PRINTF_STATE_LENGTH_LONG;
                                break;
                    default:    goto PRINTF_STATE_SPEC_;
                }
                break;

            case PRINTF_STATE_LENGTH_SHORT:
                if (*fmt == 'h')
                {
                    length = PRINTF_LENGTH_SHORT_SHORT;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_LENGTH_LONG:
                if (*fmt == 'l')
                {
                    length = PRINTF_LENGTH_LONG_LONG;
                    state = PRINTF_STATE_SPEC;
                }
                else goto PRINTF_STATE_SPEC_;
                break;

            case PRINTF_STATE_SPEC:
            PRINTF_STATE_SPEC_:
                switch (*fmt)
                {
                    case 'c':   putc((char)va_arg(args, int)); break;
                    case 's':   puts(va_arg(args, const char*)); break;
                    case '%':   putc('%'); break;

                    case 'd':
                    case 'i':   radix = 10; sign = true; number = true; break;
                    case 'u':   radix = 10; sign = false; number = true; break;
                    case 'x':
                    case 'X':
                    case 'p':   radix = 16; sign = false; number = true; break;
                    case 'o':   radix = 8; sign = false; number = true; break;

                    default: break;
                }

                if (number)
                {
                    if (sign)
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     printf_signed(va_arg(args, int), radix); break;
                        case PRINTF_LENGTH_LONG:        printf_signed(va_arg(args, long), radix); break;
                        case PRINTF_LENGTH_LONG_LONG:   printf_signed(va_arg(args, long long), radix); break;
                        }
                    }
                    else
                    {
                        switch (length)
                        {
                        case PRINTF_LENGTH_SHORT_SHORT:
                        case PRINTF_LENGTH_SHORT:
                        case PRINTF_LENGTH_DEFAULT:     printf_unsigned(va_arg(args, unsigned int), radix); break;
                        case PRINTF_LENGTH_LONG:        printf_unsigned(va_arg(args, unsigned long), radix); break;
                        case PRINTF_LENGTH_LONG_LONG:   printf_unsigned(va_arg(args, unsigned long long), radix); break;
                        }
                    }
                }

                state = PRINTF_STATE_NORMAL;
                length = PRINTF_LENGTH_DEFAULT;
                radix = 10;
                sign = false;
                number = false;
                break;
        }

        fmt++;
    }

    va_end(args);
}

void print_buffer(const char* msg, const void* buffer, uint32_t count)
{
    const uint8_t* u8Buffer = (const uint8_t*)buffer;
    
    puts(msg);
    for (uint32_t i = 0; i < count; i++)
    {
        putc(g_HexChars[u8Buffer[i] >> 4]);
        putc(g_HexChars[u8Buffer[i] & 0xF]);
    }
    puts("\n");
}

char* scan() {
    // Clear buffer
    for (int i = 0; i < 256; i++) {
        buffer[i] = '\0';
    }

    int index = 0;
    bool key_pressed = false;
    int startX = screenX;
    int startY = screenY;

    while(true) {
        int key = keyboard_get_key();
        
        if (key != -1) {
            if (!key_pressed) {  // Only process on new key press
                key_pressed = true;
                
                if (key == BACKSPACE) {
                    if (index > 0 && screenX > startX) {
                        index--;
                        buffer[index] = '\0';
                        putb();
                    }
                } 
                else if (key == ENTER) {
                    putc('\n');
                    buffer[index] = '\0';
                    break;
                } 
                else if (key >= 0) {
                    if (index < 255) {
                        buffer[index++] = sc_ascii[key];
                        putc(sc_ascii[key]);
                    }
                }
            }
        } else {
            key_pressed = false;  // Reset when key is released
        }
    }
    return buffer;
}