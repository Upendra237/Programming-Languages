/*
 * Simple Calculator - A beginner-friendly C calculator program
 * 
 * This program demonstrates basic C concepts including:
 * - Functions and modularity
 * - User input processing
 * - Basic arithmetic operations
 * - Control flow with loops and conditions
 * - Error handling
 *
 * Author: Upendra237
 * GitHub: https://github.com/Upendra237
 */

 #include <stdio.h>  // Only header needed for basic input/output

 /* Function declarations (prototypes) */
 
 // Basic arithmetic operations
 double add(double a, double b);
 double subtract(double a, double b);
 double multiply(double a, double b);
 double divide(double a, double b);
 double modulus(double a, double b);
 double power(double a, double b);
 
 // Mathematical functions
 double square_root(double a);
 double absolute_value(double a);
 double round_number(double a);
 double ceiling(double a);
 double floor_number(double a);
 
 // Simple transformations
 double increment(double a);
 double decrement(double a);
 double double_value(double a);
 double half_value(double a);
 double square(double a);
 double cube(double a);
 
 // Comparison functions
 double maximum(double a, double b);
 double minimum(double a, double b);
 double average(double a, double b);
 
 // Boolean checks (returns 1 for true, 0 for false)
 double is_positive(double a);
 double is_negative(double a);
 double is_zero(double a);
 
 // Helper functions
 void clear_screen();
 void display_help();
 void process_command(char *input);
 int string_compare(const char *str1, const char *str2);
 
 /**
  * Main function - program entry point
  */
 int main() {
     char input[50];      // Array to store user input (up to 50 characters)
     int running = 1;     // Flag to control the main loop
     
     printf("=== Simple Calculator ===\n");
     printf("Type 'help' for commands, 'cls' to clear screen, 'exit' to quit\n\n");
     
     // Main program loop - runs until user enters "exit"
     while (running) {
         printf("Calculate> ");              // Display prompt
         fgets(input, 50, stdin);            // Read what user types (safely)
         
         // Remove newline character from input
         for (int i = 0; input[i] != '\0'; i++) {
             if (input[i] == '\n') {
                 input[i] = '\0';            // Replace newline with string terminator
                 break;
             }
         }
         
         // Check for exit command
         if (string_compare(input, "exit") == 0) {
             running = 0;                    // Set flag to exit the loop
             printf("Goodbye!\n");
             continue;                       // Skip to next iteration (which will exit)
         }
         
         // Check for clear screen command
         if (string_compare(input, "cls") == 0) {
             clear_screen();
             continue;                       // Skip to next iteration
         }
         
         // Check for help command
         if (string_compare(input, "help") == 0) {
             display_help();
             continue;                       // Skip to next iteration
         }
         
         // Process calculation commands
         process_command(input);
     }
     
     return 0;                              // Indicate successful program completion
 }
 
 /**
  * Compare two strings (similar to strcmp)
  * Returns 0 if equal, non-zero if different
  */
 int string_compare(const char *str1, const char *str2) {
     int i = 0;
     
     // Loop until we find different characters or reach the end of both strings
     while (str1[i] != '\0' && str2[i] != '\0') {
         if (str1[i] != str2[i]) {
             return str1[i] - str2[i];       // Return difference
         }
         i++;
     }
     
     // If we reached the end of one string but not the other
     return str1[i] - str2[i];
 }
 
 /**
  * Function to clear the screen using ANSI escape codes
  * Works on most terminals including Linux, macOS, and modern Windows
  */
 void clear_screen() {
     // ANSI escape code to clear screen and move cursor to home position
     printf("\033[2J\033[H");
 }
 
 /**
  * Display help information about available commands
  */
 void display_help() {
     printf("\n=== Calculator Commands ===\n");
     
     printf("Two-number operations:\n");
     printf("  a + b    : Addition\n");
     printf("  a - b    : Subtraction\n");
     printf("  a * b    : Multiplication\n");
     printf("  a / b    : Division\n");
     printf("  a %% b    : Modulus (remainder)\n");
     printf("  a ^ b    : Power (a raised to power b)\n");
     printf("  max a b  : Maximum value\n");
     printf("  min a b  : Minimum value\n");
     printf("  avg a b  : Average value\n");
     
     printf("\nSingle-number operations:\n");
     printf("  sqrt a   : Square root\n");
     printf("  abs a    : Absolute value\n");
     printf("  round a  : Round to nearest integer\n");
     printf("  ceil a   : Round up to nearest integer\n");
     printf("  floor a  : Round down to nearest integer\n");
     printf("  inc a    : Increment by 1\n");
     printf("  dec a    : Decrement by 1\n");
     printf("  double a : Multiply by 2\n");
     printf("  half a   : Divide by 2\n");
     printf("  square a : Square the number\n");
     printf("  cube a   : Cube the number\n");
     
     printf("\nCheck operations (returns 1 for true, 0 for false):\n");
     printf("  pos a    : Is positive?\n");
     printf("  neg a    : Is negative?\n");
     printf("  zero a   : Is zero?\n");
     
     printf("\nOther commands:\n");
     printf("  cls      : Clear screen\n");
     printf("  exit     : Exit program\n");
     printf("  help     : Show this help\n\n");
 }
 
 /**
  * Process the calculation command entered by the user
  */
 void process_command(char *input) {
     double num1, num2, result;
     
     // Two-number operations
     if (sscanf(input, "%lf + %lf", &num1, &num2) == 2) {
         result = add(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "%lf - %lf", &num1, &num2) == 2) {
         result = subtract(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "%lf * %lf", &num1, &num2) == 2) {
         result = multiply(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "%lf / %lf", &num1, &num2) == 2) {
         result = divide(num1, num2);
         if (result == -1) {
             printf("Error: Cannot divide by zero\n");
         } else {
             printf("%.2f\n", result);
         }
     }
     else if (sscanf(input, "%lf %% %lf", &num1, &num2) == 2) {
         result = modulus(num1, num2);
         if (result == -1) {
             printf("Error: Cannot find modulus with zero divisor\n");
         } else {
             printf("%.2f\n", result);
         }
     }
     else if (sscanf(input, "%lf ^ %lf", &num1, &num2) == 2) {
         result = power(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "max %lf %lf", &num1, &num2) == 2) {
         result = maximum(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "min %lf %lf", &num1, &num2) == 2) {
         result = minimum(num1, num2);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "avg %lf %lf", &num1, &num2) == 2) {
         result = average(num1, num2);
         printf("%.2f\n", result);
     }
     
     // One-number operations
     else if (sscanf(input, "sqrt %lf", &num1) == 1) {
         result = square_root(num1);
         if (result == -1) {
             printf("Error: Cannot calculate square root of negative number\n");
         } else {
             printf("%.2f\n", result);
         }
     }
     else if (sscanf(input, "abs %lf", &num1) == 1) {
         result = absolute_value(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "round %lf", &num1) == 1) {
         result = round_number(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "ceil %lf", &num1) == 1) {
         result = ceiling(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "floor %lf", &num1) == 1) {
         result = floor_number(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "inc %lf", &num1) == 1) {
         result = increment(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "dec %lf", &num1) == 1) {
         result = decrement(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "double %lf", &num1) == 1) {
         result = double_value(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "half %lf", &num1) == 1) {
         result = half_value(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "square %lf", &num1) == 1) {
         result = square(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "cube %lf", &num1) == 1) {
         result = cube(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "pos %lf", &num1) == 1) {
         result = is_positive(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "neg %lf", &num1) == 1) {
         result = is_negative(num1);
         printf("%.2f\n", result);
     }
     else if (sscanf(input, "zero %lf", &num1) == 1) {
         result = is_zero(num1);
         printf("%.2f\n", result);
     }
     else {
         printf("Error: Unrecognized command. Type 'help' for available commands.\n");
     }
 }
 
 /*
  * Implementation of arithmetic operations
  */
 
 /**
  * Add two numbers and return the result
  */
 double add(double a, double b) {
     return a + b;
 }
 
 /**
  * Subtract second number from first and return the result
  */
 double subtract(double a, double b) {
     return a - b;
 }
 
 /**
  * Multiply two numbers and return the result
  */
 double multiply(double a, double b) {
     return a * b;
 }
 
 /**
  * Divide first number by second, returns -1 if second number is zero
  */
 double divide(double a, double b) {
     if (b == 0) {
         return -1;  // Error flag for division by zero
     }
     return a / b;
 }
 
 /**
  * Calculate remainder when first number is divided by second
  * Returns -1 if second number is zero
  */
 double modulus(double a, double b) {
     if (b == 0) {
         return -1;  // Error flag for modulus by zero
     }
     // Convert to integers since modulus typically works with integers
     return (int)a % (int)b;
 }
 
 /**
  * Calculate the power of first number raised to second number
  * This simple implementation works for integer exponents
  */
 double power(double a, double b) {
     // Base case for any number raised to power 0
     if (b == 0) {
         return 1;
     }
     
     double result = 1;
     int exponent = (int)b;  // Convert to integer
     
     // Handle negative exponents
     if (exponent < 0) {
         a = 1 / a;
         exponent = -exponent;
     }
     
     // Multiply the base by itself 'exponent' times
     for (int i = 0; i < exponent; i++) {
         result *= a;
     }
     
     return result;
 }
 
 /*
  * Implementation of mathematical functions
  */
 
 /**
  * Calculate square root using Newton's method
  * Returns -1 for negative inputs (error)
  */
 double square_root(double a) {
     if (a < 0) {
         return -1;  // Error flag for negative input
     }
     
     // Handle special cases
     if (a == 0 || a == 1) {
         return a;
     }
     
     // Newton's method for square root approximation
     double guess = a / 2;  // Initial guess
     
     // Iteratively improve the guess
     for (int i = 0; i < 10; i++) {
         guess = (guess + a / guess) / 2;
     }
     
     return guess;
 }
 
 /**
  * Return the absolute value of a number
  */
 double absolute_value(double a) {
     if (a < 0) {
         return -a;  // Return the negative of a negative number
     }
     return a;
 }
 
 /**
  * Round a number to the nearest integer
  */
 double round_number(double a) {
     if (a >= 0) {
         return (int)(a + 0.5);  // Add 0.5 and truncate for positive numbers
     } else {
         return (int)(a - 0.5);  // Subtract 0.5 and truncate for negative numbers
     }
 }
 
 /**
  * Round a number up to the nearest integer (ceiling)
  */
 double ceiling(double a) {
     int i = (int)a;  // Truncate to get integer part
     
     // If a is already an integer, return it
     if (a == i) {
         return a;
     }
     
     // If a is positive and has a fractional part, round up
     if (a > 0) {
         return i + 1;
     }
     
     // If a is negative, the truncated value is the ceiling
     return i;
 }
 
 /**
  * Round a number down to the nearest integer (floor)
  */
 double floor_number(double a) {
     int i = (int)a;  // Truncate to get integer part
     
     // If a is already an integer or positive, truncation is the floor
     if (a == i || a >= 0) {
         return i;
     }
     
     // If a is negative and has a fractional part, round down
     return i - 1;
 }
 
 /*
  * Implementation of simple transformations
  */
 
 /**
  * Add 1 to a number
  */
 double increment(double a) {
     return a + 1;
 }
 
 /**
  * Subtract 1 from a number
  */
 double decrement(double a) {
     return a - 1;
 }
 
 /**
  * Multiply a number by 2
  */
 double double_value(double a) {
     return a * 2;
 }
 
 /**
  * Divide a number by 2
  */
 double half_value(double a) {
     return a / 2;
 }
 
 /**
  * Multiply a number by itself
  */
 double square(double a) {
     return a * a;
 }
 
 /**
  * Multiply a number by itself twice
  */
 double cube(double a) {
     return a * a * a;
 }
 
 /*
  * Implementation of comparison functions
  */
 
 /**
  * Return the larger of two numbers
  */
 double maximum(double a, double b) {
     if (a > b) {
         return a;
     }
     return b;
 }
 
 /**
  * Return the smaller of two numbers
  */
 double minimum(double a, double b) {
     if (a < b) {
         return a;
     }
     return b;
 }
 
 /**
  * Return the average of two numbers
  */
 double average(double a, double b) {
     return (a + b) / 2;
 }
 
 /*
  * Implementation of boolean checks
  */
 
 /**
  * Return 1 if number is positive, 0 otherwise
  */
 double is_positive(double a) {
     return (a > 0) ? 1 : 0;
 }
 
 /**
  * Return 1 if number is negative, 0 otherwise
  */
 double is_negative(double a) {
     return (a < 0) ? 1 : 0;
 }
 
 /**
  * Return 1 if number is zero, 0 otherwise
  */
 double is_zero(double a) {
     return (a == 0) ? 1 : 0;
 }