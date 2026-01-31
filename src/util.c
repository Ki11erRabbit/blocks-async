#include "util.h"

#define UTF8_MULTIBYTE_BIT BIT(7)

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b > 0) {
        const unsigned int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

size_t truncate_utf8_string(char* const buffer, const size_t size,
                            const size_t char_limit) {
    size_t char_count = 0;
    size_t i = 0;
    while (char_count < char_limit) {
        char ch = buffer[i];
        if (ch == '\0') {
            break;
        }

        unsigned short skip = 1;
        
        // Skip status2d escape sequences (^c, ^b, ^d, ^f, ^r)
        if (ch == '^' && i + 1 < size) {
            char next = buffer[i + 1];
            if (next == 'c' || next == 'b') {
                // ^c#RRGGBB^ or ^b#RRGGBB^ - skip to next ^
                skip = 1;
                while (i + skip < size && buffer[i + skip] != '^' && buffer[i + skip] != '\0') {
                    ++skip;
                }
                if (i + skip < size && buffer[i + skip] == '^') {
                    ++skip; // include closing ^
                }
                i += skip;
                continue; // Don't increment char_count for escape sequences
            } else if (next == 'd' || next == 'f' || next == 'r') {
                // ^d^, ^f^, ^r^ - skip these
                i += 3; // skip ^X^
                continue;
            }
        }

        // Multibyte unicode character.
        if ((ch & UTF8_MULTIBYTE_BIT) != 0) {
            // Skip continuation bytes.
            ch <<= 1;
            while ((ch & UTF8_MULTIBYTE_BIT) != 0) {
                ch <<= 1;
                ++skip;
            }
        }

        // Avoid buffer overflow.
        if (i + skip >= size) {
            break;
        }

        ++char_count;
        i += skip;
    }

    buffer[i] = '\0';

    return i + 1;
}
