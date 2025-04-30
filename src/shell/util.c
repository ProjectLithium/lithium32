#include "util.h"
#include <std/string.h>

#define MAX_WORDS 32
#define MAX_WORD_LENGTH 64

char** split(char* str)
{
    static char result[MAX_WORDS][MAX_WORD_LENGTH]; // static for persistent return
    static char* pointers[MAX_WORDS];               // array of pointers to result[i]
    
    int word_index = 0;
    int char_index = 0;

    for (int i = 0; i < MAX_WORDS; i++) {
        pointers[i] = result[i]; // set pointers to the buffers
        result[i][0] = '\0';     // initialize with empty string
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            if (char_index > 0) { // end current word
                result[word_index][char_index] = '\0';
                word_index++;
                char_index = 0;

                if (word_index >= MAX_WORDS)
                    break;
            }
        } else {
            if (char_index < MAX_WORD_LENGTH - 1) {
                result[word_index][char_index++] = str[i];
            }
        }
    }

    if (char_index > 0 && word_index < MAX_WORDS) {
        result[word_index][char_index] = '\0'; // null-terminate last word
        word_index++;
    }

    pointers[word_index] = NULL; // NULL-terminate the array
    return pointers;
}

char* join(char** array, char symbol)
{
    static char result[256]; // Static buffer for result
    int current_len = 0;

    result[0] = '\0'; // Start with an empty string

    for (int i = 1; array[i]; i++) {
        // Ensure there's enough space in the buffer
        if (current_len + strlen(array[i]) + 1 >= 256) {
            result[0] = '\0';  // Clear the result buffer if overflow occurs
            return result;     // Return empty buffer
        }

        // Copy current word into result
        strcat(result, array[i]);
        current_len += strlen(array[i]);

        // Add symbol (space or other) between words
        if (array[i + 1]) {
            result[current_len] = symbol;
            result[current_len + 1] = '\0';
            current_len++;
        }
    }

    return result;
}