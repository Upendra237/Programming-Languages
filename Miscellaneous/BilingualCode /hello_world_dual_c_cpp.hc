/**
 * hello_world_dual_c_cpp.hc
 * =========================
 * 
 * A bilingual "Hello World" program that compiles and executes correctly
 * with both C and C++ compilers without any modification.
 * 
 * The .hc extension suggests a hybrid/compatible file that works across
 * both C and C++ environments.
 */

#ifdef __cplusplus
/* C++ compiler detected - use C++ standard library components */
#include <iostream>
#define PRINT std::cout<<"Hello World from C++"<<std::endl
#else
/* C compiler detected - use C standard library components */
#include <stdio.h>
#define PRINT printf("Hello World from C\n")
#endif

/**
 * Main function - identical syntax in both C and C++
 * The PRINT macro expands to the appropriate implementation based on compiler
 */
int main(){PRINT;return 0;}