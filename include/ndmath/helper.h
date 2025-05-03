#ifndef PROTO
#define PROTO


#include "ndarray.h"


#if defined(ENABLE_OPTIMIZATION) && ENABLE_OPTIMIZATION == 2
    // Code specific to optimization level 2
    #pragma message("Using optimization level 2")
#elif defined(ENABLE_OPTIMIZATION) && ENABLE_OPTIMIZATION == 3
    // Code specific to optimization level 3
    #pragma message("Using optimization level 3")
#else
    // Default code if optimization level is not defined or not supported
//    #pragma message("Using default optimization level")
#endif

void clean(ndarray_t* arr, ...);
void print_array(ndarray_t a, size_t dp);
void swap(double *x, double *y);
// double pow(double x, int n);
double Sqrt(double);

/*

#include <stdarg.h>
#include <stdio.h>

int sum(int x, int y, ...) {
    int result = x + y;

    va_list args;
    va_start(args, y);

    int num;
    while ((num = va_arg(args, int)) != 0) {
        result += num;
    }

    va_end(args);

    return result;
}

int main() {
    int result = sum(1, 2, 3, 4, 5, 0);
    printf("Result: %d\n", result);

    return 0;
}



*/






/**
 * 
 * 
 * The effectiveness of optimization techniques can vary depending on the specific code, hardware architecture, and compiler. However, here is a suggested combination of optimization techniques that are generally known to be effective:

1. Compiler Flags:
   - `-O3`: Enable high-level optimization. This flag typically includes a wide range of optimizations that can significantly improve performance.

2. Pragmas:
   - OpenMP:
     - `#pragma omp parallel for`: Parallelize eligible loops to execute iterations in parallel.
     - `#pragma omp simd`: Enable automatic vectorization of eligible loops using SIMD instructions.

3. Data-oriented optimizations:
   - Array of Structures (AoS) to Structure of Arrays (SoA) transformation: Reorganize data structures to improve data locality and enable better vectorization.

4. Compiler-specific pragmas:
   - G C C :
     - `#pragma GCC ivdep`: Declare that there are no loop-carried dependencies, enabling more aggressive vectorization.

5. Profile-guided optimization (PGO):
   - Collect profiling information during a representative run of the program and use it to guide optimization decisions during compilation.

6. Compiler-specific options:
   - G C C :
     - `-ftree-vectorize`: Enable automatic vectorization.
     - `-funroll-loops`: Unroll loops to reduce loop overhead.

Remember that the effectiveness of these techniques can vary depending on the specific code and hardware architecture. It's essential to profile and benchmark your code to determine the most effective combination of optimizations for your particular scenario. Additionally, consult your compiler's documentation for more detailed information on available options and their effects.
*/

#endif