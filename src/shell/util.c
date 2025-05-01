#include "util.h"
#include <std/string.h>
#include <stddef.h>
#include <stdint.h>
#include <memory/memory.h>

#define MAX_WORDS 32
#define MAX_WORD_LENGTH 64

char** split(char* str)
{
    static char result[MAX_WORDS][MAX_WORD_LENGTH];
    static char* pointers[MAX_WORDS + 1]; // +1 for NULL terminator

    // Zero initialize result buffers and pointers
    memset(result, 0, sizeof(result));
    memset(pointers, 0, sizeof(pointers));

    for (int i = 0; i < MAX_WORDS; i++) {
        pointers[i] = result[i];
    }

    int word_index = 0;
    int char_index = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            if (char_index > 0) {
                result[word_index][char_index] = '\0';
                word_index++;
                char_index = 0;
                if (word_index >= MAX_WORDS)
                    break;
            }
        } else if (char_index < MAX_WORD_LENGTH - 1) {
            result[word_index][char_index++] = str[i];
        }
    }

    if (char_index > 0 && word_index < MAX_WORDS) {
        result[word_index][char_index] = '\0';
        word_index++;
    }

    pointers[word_index] = NULL; // NULL-terminate
    return pointers;
}


char* join(char** array, char symbol)
{
    static char result[256];
    memset(result, 0, sizeof(result)); // clear buffer

    size_t current_len = 0;

    for (int i = 1; array[i]; i++) {
        size_t len = strlen(array[i]);

        // Check for overflow
        if (current_len + len + 1 >= sizeof(result)) {
            result[0] = '\0';
            return result;
        }

        memcpy(result + current_len, array[i], len);
        current_len += len;

        if (array[i + 1]) {
            result[current_len++] = symbol;
        }
    }

    result[current_len] = '\0';
    return result;
}

char* int_to_string(size_t num) {
    static char buffer[21]; // enough for 64-bit integers (20 digits + null)
    int i = 20;

    buffer[i] = '\0'; // null terminator

    if (num == 0) {
        buffer[--i] = '0';
        return &buffer[i];
    }

    while (num > 0 && i > 0) {
        buffer[--i] = '0' + (num % 10);
        num /= 10;
    }

    return &buffer[i];
}

char* str_join(const char* a, const char* b) {
    static char dest[64];
    memset(dest, 0, sizeof(dest));

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a + len_b >= sizeof(dest))
        return dest;

    memcpy(dest, a, len_a);
    memcpy(dest + len_a, b, len_b);

    dest[len_a + len_b] = '\0';
    return dest;
}
