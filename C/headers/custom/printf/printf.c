/**
 * custom_printf.c
 * 
 * A custom implementation of printf functionality for Windows
 * without using standard library header files.
 * 
 * Author: Upendra237
 * License: MIT
 */

/**
 * ========================================================================
 * WINDOWS API TYPE DEFINITIONS AND FUNCTION DECLARATIONS
 * ========================================================================
 */

// Basic Windows types
typedef unsigned long       DWORD;
typedef long                LONG;
typedef void*               HANDLE;
typedef int                 BOOL;
typedef unsigned short      WORD;
typedef unsigned char       BYTE;
typedef const char*         LPCSTR;
typedef char*               LPSTR;
typedef void*               LPVOID;
typedef DWORD*              LPDWORD;

// Windows API function prototypes with proper calling convention
extern HANDLE __attribute__((stdcall)) GetStdHandle(DWORD nStdHandle);
extern BOOL __attribute__((stdcall)) WriteConsoleA(
    HANDLE hConsoleOutput,
    const void* lpBuffer,
    DWORD nNumberOfCharsToWrite,
    DWORD* lpNumberOfCharsWritten,
    void* lpReserved
);

// Windows constants
#define STD_OUTPUT_HANDLE  ((DWORD)-11)
#define STD_ERROR_HANDLE   ((DWORD)-12)
#define FALSE              0
#define TRUE               1

/**
 * ========================================================================
 * UTILITY FUNCTIONS
 * ========================================================================
 */

/**
 * Calculate the length of a string
 * 
 * @param str The string to measure
 * @return The length of the string
 */
int my_strlen(const char* str) {
    int len = 0;
    if (!str) return 0;
    
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

/**
 * Copy a string
 * 
 * @param dest Destination buffer
 * @param src Source string
 * @return Number of characters copied
 */
int my_strcpy(char* dest, const char* src) {
    int i = 0;
    if (!dest || !src) return 0;
    
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

/**
 * Convert an integer to a string representation
 * 
 * @param num The number to convert
 * @param str The output string buffer
 * @param base The numeric base (10 for decimal, 16 for hex, etc.)
 * @return Length of the resulting string
 */
int my_itoa(int num, char* str, int base) {
    int i = 0;
    int is_negative = 0;
    
    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }
    
    // Handle negative numbers (only for base 10)
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }
    
    // Process individual digits
    while (num != 0) {
        int remainder = num % base;
        str[i++] = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        num = num / base;
    }
    
    // Add negative sign if needed
    if (is_negative) {
        str[i++] = '-';
    }
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    
    str[i] = '\0';
    return i;
}

/**
 * Convert a double to string with specified precision
 * 
 * @param num The number to convert
 * @param str The output string buffer
 * @param precision Number of decimal places
 * @return Length of the resulting string
 */
int my_dtoa(double num, char* str, int precision) {
    int pos = 0;
    
    // Handle negative numbers
    if (num < 0) {
        str[pos++] = '-';
        num = -num;
    }
    
    // Get the integer part
    int int_part = (int)num;
    double frac_part = num - int_part;
    
    // Convert integer part to string
    if (int_part == 0) {
        str[pos++] = '0';
    } else {
        char int_str[32];
        int len = my_itoa(int_part, int_str, 10);
        for (int i = 0; i < len; i++) {
            str[pos++] = int_str[i];
        }
    }
    
    // Add decimal point and fractional part if precision > 0
    if (precision > 0) {
        str[pos++] = '.';
        
        // Calculate power of 10 for precision
        int power = 1;
        for (int i = 0; i < precision; i++) {
            power *= 10;
        }
        
        // Convert fractional part
        int frac_int = (int)(frac_part * power + 0.5); // Round
        
        // Add leading zeros if needed
        int frac_digits = 0;
        int temp = frac_int;
        while (temp > 0) {
            temp /= 10;
            frac_digits++;
        }
        
        // Handle case where frac_int is 0
        if (frac_int == 0) {
            for (int i = 0; i < precision; i++) {
                str[pos++] = '0';
            }
        } else {
            // Add leading zeros
            for (int i = 0; i < precision - frac_digits; i++) {
                str[pos++] = '0';
            }
            
            // Add fractional digits
            char frac_str[32];
            int len = my_itoa(frac_int, frac_str, 10);
            for (int i = 0; i < len; i++) {
                str[pos++] = frac_str[i];
            }
        }
    }
    
    str[pos] = '\0';
    return pos;
}

/**
 * Convert an unsigned integer to a string representation
 * 
 * @param num The number to convert
 * @param str The output string buffer
 * @param base The numeric base (10 for decimal, 16 for hex, etc.)
 * @return Length of the resulting string
 */
int my_uitoa(unsigned int num, char* str, int base) {
    int i = 0;
    
    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }
    
    // Process individual digits
    while (num != 0) {
        int remainder = num % base;
        str[i++] = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        num = num / base;
    }
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    
    str[i] = '\0';
    return i;
}

/**
 * ========================================================================
 * CORE PRINTF FUNCTIONALITY
 * ========================================================================
 */

/**
 * Write a string to the console using Windows API
 * 
 * @param str The string to write
 * @param len Length of the string
 * @return Number of characters written, -1 on error
 */
int write_console(const char* str, int len) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;
    
    if (hConsole == (void*)-1) {
        return -1;  // Error getting console handle
    }
    
    if (!WriteConsoleA(hConsole, str, len, &written, 0)) {
        return -1;  // Error writing to console
    }
    
    return (int)written;
}

/**
 * Format a single item based on format specifier
 * 
 * @param buffer Output buffer
 * @param buffer_pos Current position in buffer
 * @param format Format character ('d', 's', etc.)
 * @param width Field width (0 if not specified)
 * @param precision Precision for floating point (default 6)
 * @param flags Formatting flags
 * @param args Pointer to current argument
 * @param arg_index Current argument index
 * @return New position in buffer
 */
int format_arg(char* buffer, int buffer_pos, 
               char format, int width, int precision, int flags,
               int* args, int* arg_index) {
    
    char temp[128];
    int len = 0;
    int padding = 0;
    
    // Default precision for floating point
    if (precision < 0 && (format == 'f' || format == 'g')) {
        precision = 6;
    }
    
    switch (format) {
        case 'd': 
        case 'i': {
            // Integer
            int value = args[(*arg_index)++];
            len = my_itoa(value, temp, 10);
            break;
        }
        case 'u': {
            // Unsigned integer
            unsigned int value = (unsigned int)args[(*arg_index)++];
            len = my_uitoa(value, temp, 10);
            break;
        }
        case 'x': {
            // Hexadecimal (lowercase)
            unsigned int value = (unsigned int)args[(*arg_index)++];
            len = my_uitoa(value, temp, 16);
            break;
        }
        case 'X': {
            // Hexadecimal (uppercase)
            unsigned int value = (unsigned int)args[(*arg_index)++];
            len = my_uitoa(value, temp, 16);
            // Convert to uppercase
            for (int i = 0; i < len; i++) {
                if (temp[i] >= 'a' && temp[i] <= 'f') {
                    temp[i] = temp[i] - 'a' + 'A';
                }
            }
            break;
        }
        case 'c': {
            // Character
            char value = (char)args[(*arg_index)++];
            temp[0] = value;
            len = 1;
            temp[1] = '\0';
            break;
        }
        case 's': {
            // String
            char* value = (char*)args[(*arg_index)++];
            if (value) {
                len = my_strlen(value);
                if (precision >= 0 && len > precision) {
                    len = precision;
                }
                // Copy at most 'len' characters
                for (int i = 0; i < len; i++) {
                    temp[i] = value[i];
                }
                temp[len] = '\0';
            } else {
                my_strcpy(temp, "(null)");
                len = 6;
            }
            break;
        }
        case 'f': {
            // Floating point
            // Need to handle double arguments carefully
            double value;
            if (sizeof(int) == sizeof(void*)) {
                // 32-bit system, doubles use two slots
                value = *(double*)&args[*arg_index];
                (*arg_index) += 2;  // Double uses 2 int slots
            } else {
                // 64-bit system
                value = *(double*)&args[*arg_index];
                (*arg_index) += 1;
            }
            
            len = my_dtoa(value, temp, precision >= 0 ? precision : 6);
            break;
        }
        case 'p': {
            // Pointer
            void* value = (void*)args[(*arg_index)++];
            my_strcpy(temp, "0x");
            len = 2 + my_uitoa((unsigned int)value, temp + 2, 16);
            break;
        }
        case '%': {
            // Percent sign
            temp[0] = '%';
            len = 1;
            temp[1] = '\0';
            break;
        }
        default: {
            // Unknown format, output as-is
            temp[0] = '%';
            temp[1] = format;
            len = 2;
            temp[2] = '\0';
            break;
        }
    }
    
    // Apply padding if width specified
    if (width > len) {
        padding = width - len;
    }
    
    // Copy formatted result to buffer
    if (padding > 0) {
        // Right align by default
        for (int i = 0; i < padding; i++) {
            buffer[buffer_pos++] = ' ';
        }
    }
    
    for (int i = 0; i < len; i++) {
        buffer[buffer_pos++] = temp[i];
    }
    
    return buffer_pos;
}

/**
 * Parse format string for width, precision, and flags
 * 
 * @param format Format string
 * @param pos Current position in format string
 * @param width Output parameter for field width
 * @param precision Output parameter for precision
 * @param flags Output parameter for formatting flags
 * @return New position in format string
 */
int parse_format(const char* format, int pos, 
                int* width, int* precision, int* flags) {
    *width = 0;
    *precision = -1;
    *flags = 0;
    
    // Parse width
    while (format[pos] >= '0' && format[pos] <= '9') {
        *width = (*width * 10) + (format[pos] - '0');
        pos++;
    }
    
    // Parse precision
    if (format[pos] == '.') {
        pos++;
        *precision = 0;
        while (format[pos] >= '0' && format[pos] <= '9') {
            *precision = (*precision * 10) + (format[pos] - '0');
            pos++;
        }
    }
    
    return pos;
}

/**
 * Custom printf implementation without standard library headers
 * 
 * @param format Format string with specifiers
 * @param ... Variable arguments corresponding to format specifiers
 * @return Number of characters written
 */
int custom_printf(const char* format, ...) {
    if (!format) return 0;
    
    char buffer[4096]; // Large output buffer for safety
    int buffer_pos = 0;
    int total_written = 0;
    
    // Get a pointer to the first argument after format
    int* args = (int*)&format + 1;
    int arg_index = 0;
    
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i+1] != '\0') {
            i++; // Move to character after %
            
            // Parse format specifiers
            int width = 0;
            int precision = -1;
            int flags = 0;
            
            i = parse_format(format, i, &width, &precision, &flags);
            
            // Format the argument
            buffer_pos = format_arg(buffer, buffer_pos, format[i], 
                                  width, precision, flags, 
                                  args, &arg_index);
        } else {
            // Regular character
            buffer[buffer_pos++] = format[i];
        }
        
        // Flush buffer if getting full
        if (buffer_pos > 4000) {
            int written = write_console(buffer, buffer_pos);
            if (written < 0) return -1;
            total_written += written;
            buffer_pos = 0;
        }
    }
    
    // Flush remaining buffer
    if (buffer_pos > 0) {
        int written = write_console(buffer, buffer_pos);
        if (written < 0) return -1;
        total_written += written;
    }
    
    return total_written;
}

/**
 * ========================================================================
 * MAIN FUNCTION FOR DEMONSTRATION
 * ========================================================================
 */

/**
 * Main function demonstrating the custom printf implementation
 */
int main() {
    custom_printf("========== CUSTOM PRINTF DEMONSTRATION ==========\n\n");
    
    custom_printf("Basic formatting:\n");
    custom_printf("String: %s\n", "Hello, World!");
    custom_printf("Character: %c\n", 'A');
    custom_printf("Integer: %d\n", 12345);
    custom_printf("Negative: %d\n", -789);
    custom_printf("Unsigned: %u\n", 50000);
    custom_printf("Hex (lowercase): %x\n", 255);
    custom_printf("Hex (uppercase): %X\n", 255);
    custom_printf("Pointer: %p\n", &main);
    custom_printf("Float: %f\n", 3.14159);
    custom_printf("Percentage sign: %%\n");
    
    custom_printf("\nWidth and precision:\n");
    custom_printf("Width 10: '%10d'\n", 123);
    custom_printf("Precision 2: '%.2f'\n", 3.14159);
    custom_printf("Width and precision: '%10.2f'\n", 3.14159);
    
    custom_printf("\nMixed formatting:\n");
    custom_printf("Mixed: %d %s %c\n", 42, "is the answer", '!');
    custom_printf("Multiple arguments: %d, %d, %d, %d\n", 1, 2, 3, 4);
    
    custom_printf("\n===================================================\n");
    
    return 0;
}
