#include "Monitor.h"
#include <stdarg.h>

/**
 * @brief Enhanced printf implementation for UART output
 * Supports %u, %d, %s and ANSI escape sequences
 */
void uart_printf(const char* format, ...) 
{
    const char *src;
    char buffer[512];  // Increased buffer size for ANSI sequences
    char *dst;
    va_list args;
    unsigned int number;
    int signed_number;
    char *string_arg;
    char num_str[12];
    int i, j;
    int has_format = 0;
    
    if (!format) return;
    
    // Check if format string contains any format specifiers
    src = format;
    while (*src) {
        if (*src == '%' && *(src + 1) && (*(src + 1) == 'u' || *(src + 1) == 'd' || *(src + 1) == 's')) {
            has_format = 1;
            break;
        }
        src++;
    }
    
    src = format;
    dst = buffer;
    
    if (has_format) {
        va_start(args, format);
        
        while (*src && (dst - buffer) < sizeof(buffer) - 20) {
            if (*src == '%' && *(src + 1)) {
                if (*(src + 1) == 'u') {
                    // Unsigned integer
                    number = va_arg(args, unsigned int);
                    
                    i = 0;
                    if (number == 0) {
                        num_str[i++] = '0';
                    } else {
                        while (number > 0) {
                            num_str[i++] = '0' + (number % 10);
                            number /= 10;
                        }
                    }
                    
                    // Copy digits in reverse order
                    for (j = i - 1; j >= 0; j--) {
                        *dst++ = num_str[j];
                    }
                    
                    src += 2; // Skip %u
                } else if (*(src + 1) == 'd') {
                    // Signed integer
                    signed_number = va_arg(args, int);
                    
                    if (signed_number < 0) {
                        *dst++ = '-';
                        signed_number = -signed_number;
                    }
                    
                    i = 0;
                    if (signed_number == 0) {
                        num_str[i++] = '0';
                    } else {
                        while (signed_number > 0) {
                            num_str[i++] = '0' + (signed_number % 10);
                            signed_number /= 10;
                        }
                    }
                    
                    // Copy digits in reverse order
                    for (j = i - 1; j >= 0; j--) {
                        *dst++ = num_str[j];
                    }
                    
                    src += 2; // Skip %d
                } else if (*(src + 1) == 's') {
                    // String
                    string_arg = va_arg(args, char*);
                    if (string_arg) {
                        while (*string_arg && (dst - buffer) < sizeof(buffer) - 10) {
                            *dst++ = *string_arg++;
                        }
                    }
                    
                    src += 2; // Skip %s
                } else {
                    // Unknown format specifier, just copy
                    *dst++ = *src++;
                }
            } else {
                // Regular character (including ANSI escape sequences)
                *dst++ = *src++;
            }
        }
        
        va_end(args);
    } else {
        // No format specifiers, just copy the string (supports ANSI sequences)
        while (*src && (dst - buffer) < sizeof(buffer) - 1) {
            *dst++ = *src++;
        }
    }
    
    *dst = '\0';
    Uart_String_Send(buffer);
}
