# 🧮 NDMath - Numerical & Data Math Library

**NDMath** is a lightweight, portable C library for numerical computations with multi-dimensional arrays (`ndarray_t`). It emphasizes **random number generation**, **explicit data copying** (no shared views), and **state independence**, making it ideal for scientific computing, data analysis, and mathematical modeling. Designed for **ease of integration**, NDMath can be used as a static (`libndmath.a`) or dynamic (`libndmath.so`) library, and it supports cross-platform compatibility (Unix/Windows with minor adjustments).

This README is tailored for beginners in C, providing step-by-step instructions to set up, use, and integrate NDMath into your projects, along with examples and explanations of its extensive capabilities.

---

## 📑 Table of Contents
- [🧮 NDMath - Numerical \& Data Math Library](#-ndmath---numerical--data-math-library)
  - [📑 Table of Contents](#-table-of-contents)
  - [🌟 Overview](#-overview)
  - [🚀 Features](#-features)
  - [🛠 Prerequisites](#-prerequisites)
  - [📦 Installation](#-installation)
    - [1. Download the Source](#1-download-the-source)
    - [2. Directory Structure](#2-directory-structure)
    - [3. Build the Library](#3-build-the-library)
      - [Using the Makefile](#using-the-makefile)
      - [Manual Compilation](#manual-compilation)
    - [4. Install the Library (Optional)](#4-install-the-library-optional)
    - [5. Compile a Program](#5-compile-a-program)
  - [📂 Library Structure](#-library-structure)
  - [🧠 Core Concepts](#-core-concepts)
  - [🚀 Getting Started](#-getting-started)
  - [📚 Functionalities](#-functionalities)
    - [Array Creation](#array-creation)
    - [Input/Output Operations](#inputoutput-operations)
    - [Mathematical Operations](#mathematical-operations)
    - [Linear Algebra](#linear-algebra)
    - [Statistics](#statistics)
    - [Random Number Generation](#random-number-generation)
    - [Trigonometric Functions](#trigonometric-functions)
  - [⚠️ Error Handling](#️-error-handling)
  - [🔗 Integration in External Projects](#-integration-in-external-projects)
    - [1. Static Linking (`libndmath.a`)](#1-static-linking-libndmatha)
    - [2. Dynamic Linking (`libndmath.so`)](#2-dynamic-linking-libndmathso)
    - [3. Direct Source Inclusion](#3-direct-source-inclusion)
    - [Makefile for External Projects](#makefile-for-external-projects)
    - [Verifying the Library](#verifying-the-library)
  - [🧪 Testing](#-testing)
  - [📦 Example Program](#-example-program)
  - [🔍 Troubleshooting](#-troubleshooting)
  - [🤝 Contributing](#-contributing)
  - [🧹 Cleaning Up](#-cleaning-up)

---

## 🌟 Overview

NDMath is inspired by Python's NumPy but implemented in C for performance and portability. It provides a robust framework for working with 2D arrays (`ndarray_t`), supporting operations like:
- Array creation and manipulation (e.g., reshaping, slicing).
- Mathematical operations (e.g., addition, transposition).
- Linear algebra (e.g., matrix inversion, eigenvalues).
- Statistical analysis (e.g., mean, variance).
- Random number generation (e.g., uniform, normal distributions).
- Trigonometric functions (e.g., sine, cosine).

NDMath is designed to be **lightweight**, **portable**, and **easy to integrate** into other projects, with no external dependencies beyond the C standard library and the math library (`-lm`).

---

## 🚀 Features

- **Explicit Data Copying**: All functions return new, dynamically allocated arrays, avoiding shared memory issues.
- **Random Number Generation**: Uses a 64-bit Linear Congruential Generator (LCG) for deterministic pseudo-random sequences.
- **Memory Management**: Manual memory handling with `clean()` to prevent leaks.
- **Cross-Platform**: Works on Unix and Windows with minimal adjustments.
- **Comprehensive Error Handling**: Descriptive error messages for common issues (e.g., null pointers, invalid dimensions).
- **Optimized Performance**: Uses GCC optimization flags (e.g., `-O3`, `unroll-loops`) for critical operations.
- **Extensive Functionality**: Supports array operations, linear algebra, statistics, and more.

---

## 🛠 Prerequisites

To use NDMath, you need:
- A C compiler (e.g., `gcc` on Linux/Mac, MinGW on Windows).
- Basic C knowledge (e.g., variables, functions, pointers).
- The math library (`-lm`) for mathematical functions.
- A text editor or IDE (e.g., VS Code, Code::Blocks).
- (Optional) `make` for automated builds using the provided `Makefile`.

---

## 📦 Installation

### 1. Download the Source
Obtain the NDMath source files (e.g., `array.c`, `random.c`, `error.c`, etc.) from the repository or source. The files are typically organized in directories like:
- `src/` (or directly `ndmath/`): Source files (`.c`).
- `include/` (or `ndmath/`): Header files (`.h`).
- `tests/`: Test files.
- `examples/`: Example programs.

### 2. Directory Structure
Ensure the files are organized as follows:
```
ndmath/
├── src/
│   ├── array.c
│   ├── random.c
│   ├── error.c
│   ├── io.c
│   ├── operations.c
│   ├── linalg.c
│   ├── statistics.c
│   ├── trig.c
│   ├── conditionals.c
│   ├── helper.c
├── include/
│   ├── ndmath/
│   │   ├── array.h
│   │   ├── random.h
│   │   ├── error.h
│   │   ├── io.h
│   │   ├── operations.h
│   │   ├── linalg.h
│   │   ├── statistics.h
│   │   ├── trig.h
│   │   ├── conditionals.h
│   │   ├── helper.h
├── tests/
│   ├── test_rand.c
├── examples/
│   ├── example.c
├── Makefile
```

### 3. Build the Library
Use the provided `Makefile` for automated builds or compile manually.

#### Using the Makefile
Run:
```bash
make all
```
This creates:
- `build/lib/libndmath.a` (static library).
- `build/lib/libndmath.so` (shared library).
- Object files in `build/obj/`.

To build only the static library:
```bash
make static
```
To build only the shared library:
```bash
make shared
```

#### Manual Compilation
If you prefer manual compilation:
```bash
# Compile object files
gcc -c -fPIC -Iinclude src/*.c -o build/obj/ndmath.o

# Create static library
ar rcs build/lib/libndmath.a build/obj/*.o

# Create shared library
gcc -shared -o build/lib/libndmath.so build/obj/*.o -lm
```

### 4. Install the Library (Optional)
To install NDMath system-wide:
```bash
make install DESTDIR=/usr/local
```
This copies:
- Libraries to `/usr/local/lib/`.
- Headers to `/usr/local/include/ndmath/`.
- Creates a symbolic link for the shared library.

### 5. Compile a Program
To use NDMath in your program, link against the library:
```bash
gcc -Iinclude my_program.c -Lbuild/lib -lndmath -lm -o my_program
```

For dynamic linking, set the library path:
```bash
export LD_LIBRARY_PATH=build/lib:$LD_LIBRARY_PATH
./my_program
```

---

## 📂 Library Structure

NDMath is modular, with each file handling specific functionality:
- **Core Array Operations** (`array.c`): Array creation, reshaping, slicing, copying.
- **Input/Output** (`io.c`): Reading/writing arrays to files (CSV-like format).
- **Mathematical Operations** (`operations.c`): Element-wise operations, transposition, logarithms.
- **Linear Algebra** (`linalg.c`): Matrix inversion, determinants, QR decomposition, eigenvalues.
- **Statistics** (`statistics.c`): Mean, variance, standard deviation.
- **Random Number Generation** (`random.c`): Uniform, normal, and integer random arrays.
- **Trigonometric Functions** (`trig.c`): Sine, cosine, secant, etc.
- **Conditionals** (`conditionals.c`): Checks for null pointers and square matrices.
- **Error Handling** (`error.c`): Descriptive error messages and program termination.
- **Utilities** (`helper.c`): Printing arrays, memory cleanup.

Corresponding header files (e.g., `array.h`, `random.h`) declare the functions and structures.

---

## 🧠 Core Concepts

- **`ndarray_t`**: The primary data structure for 2D arrays, defined in `ndarray.h`:
  ```c
  typedef struct ndarray {
      size_t shape[3];  // [rows, cols, unused]
      double** data;    // 2D array of doubles
      struct ndarray *next; // For linked lists (not widely used)
      size_t size;      // Total elements (rows * cols)
  } ndarray_t;
  ```
  - `shape[0]`: Number of rows.
  - `shape[1]`: Number of columns.
  - `data`: Dynamically allocated 2D array.

- **Memory Management**: Arrays are dynamically allocated. Use `clean(&arr, NULL)` to free memory and prevent leaks.
- **Explicit Copying**: Functions return new arrays, never modifying inputs or sharing memory.
- **Random Number Generation**: Uses a 64-bit Linear Congruential Generator (LCG) with constants:
  - `LCG_A = 6364136223846793005ULL`
  - `LCG_C = 1ULL`
  - `LCG_M = (1ULL << 63)`
- **Error Handling**: Errors (e.g., null pointers, invalid shapes) trigger descriptive messages and exit the program.

---

## 🚀 Getting Started

Let's create a simple program to demonstrate NDMath.

1. **Create `main.c`**:
   ```c
   #include <ndmath/array.h>
   #include <ndmath/helper.h>

   int main() {
       // Create a 2x3 array of ones
       ndarray_t arr = ones(2, 3);
       // Print the array with 2 decimal places
       print_array(arr, 2);
       // Free the array
       clean(&arr, NULL);
       return 0;
   }
   ```

2. **Compile**:
   ```bash
   gcc -Iinclude main.c src/array.c src/helper.c src/error.c src/conditionals.c -lm -o main
   ```

3. **Run**:
   ```bash
   ./main
   ```

4. **Output**:
   ```
   [
     [1.00, 1.00, 1.00],
     [1.00, 1.00, 1.00]
   ]  // shape: 2x3
   ```

This program creates a 2x3 array of ones, prints it, and frees the memory.

---

## 📚 Functionalities

### Array Creation

Create and manipulate arrays with these functions:
- **`array(rows, cols)`**: Uninitialized array.
  ```c
  ndarray_t arr = array(2, 3);
  ```

- **`zeros(rows, cols)`**: Array filled with zeros.
  ```c
  ndarray_t arr = zeros(2, 3);
  ```

- **`ones(rows, cols)`**: Array filled with ones.
  ```c
  ndarray_t arr = ones(2, 3);
  ```

- **`identity(rows, cols)`**: Square identity matrix (1s on diagonal).
  ```c
  ndarray_t arr = identity(3, 3);
  ```

- **`arange(max, min, rows, cols, order)`**: Evenly spaced values in `[min, max]` (order: `"asc"` or `"dsc"`).
  ```c
  ndarray_t arr = arange(10, 0, 2, 5, "asc");
  ```

- **`linspace(max, min, spacing, rows, cols)`**: Values with custom spacing.
  ```c
  ndarray_t arr = linspace(10, 0, 0.5, 2, 10);
  ```

- **`reshape(&arr, new_rows, new_cols)`**: Reshape an array.
  ```c
  ndarray_t arr = array(2, 3);
  arr = reshape(&arr, 3, 2);
  ```

- **`copy(&arr)`**: Deep copy of an array.
  ```c
  ndarray_t copy_arr = copy(&arr);
  ```

### Input/Output Operations

- **`load_ndarray(absolute_path)`**: Load a semicolon-separated CSV file into an array.
  ```c
  ndarray_t arr = load_ndarray("data.csv");
  print_array(arr, 2);
  ```

- **`save_ndarray(&arr, absolute_path)`**: Save an array to a file.
  ```c
  ndarray_t arr = ones(2, 3);
  save_ndarray(&arr, "output.csv");
  ```

**File Format**:
- CSV-like with semicolons (`;`).
- Example `data.csv`:
  ```
  1;2;3
  4;5;6
  ```

### Mathematical Operations

- **`sum(&arr1, &arr2)`**: Element-wise addition.
  ```c
  ndarray_t result = sum(&arr1, &arr2);
  ```

- **`subtract(&arr1, &arr2)`**: Element-wise subtraction.
  ```c
  ndarray_t result = subtract(&arr1, &arr2);
  ```

- **`scaler(&arr, value, op)`**: Scalar operations (`+`, `-`, `*`, `/`).
  ```c
  ndarray_t result = scaler(&arr, 5.0, '*');
  ```

- **`transpose(&arr)`**: Transpose an array.
  ```c
  ndarray_t result = transpose(&arr);
  ```

- **`nd_log(&arr)`**, **`nd_log2(&arr)`**, **`nd_exp(&arr)`**: Logarithmic and exponential functions.
  ```c
  ndarray_t result = nd_log(&arr);
  ```

- **`ravel(&arr)`**: Flatten a 2D array into a 1D array.
  ```c
  ndarray_t result = ravel(&arr);
  ```

### Linear Algebra

- **`inv(&arr)`**: Inverse of a square matrix.
  ```c
  ndarray_t inv_arr = inv(&arr);
  ```

- **`det(&arr)`**: Determinant of a square matrix.
  ```c
  double det_val = det(&arr);
  ```

- **`matmul(&arr1, &arr2)`**: Matrix multiplication.
  ```c
  ndarray_t result = matmul(&arr1, &arr2);
  ```

- **`qr(&arr, &Q, &R)`**: QR decomposition.
  ```c
  ndarray_t Q, R;
  qr(&arr, &Q, &R);
  ```

- **`eig(&arr, niters)`**: Eigenvalues of a square matrix.
  ```c
  ndarray_t eigenvalues = eig(&arr, 1000);
  ```

- **`svd(&arr)`**: Singular values via eigenvalue decomposition.
  ```c
  ndarray_t singular_values = svd(&arr);
  ```

### Statistics

- **`mean(&arr, axis)`**: Mean along `"x"`, `"y"`, or `"all"`.
  ```c
  ndarray_t mean_arr = mean(&arr, "all");
  ```

- **`variance(&arr, axis)`**: Variance along an axis.
  ```c
  ndarray_t var_arr = variance(&arr, "x");
  ```

- **`std(&arr, axis)`**: Standard deviation.
  ```c
  ndarray_t std_arr = std(&arr, "y");
  ```

- **`argmin(&arr, axis)`**, **`argmax(&arr, axis)`**: Minimum/maximum values along an axis.
  ```c
  ndarray_t min_arr = argmin(&arr, "all");
  ```

### Random Number Generation

NDMath uses a 64-bit LCG for random number generation, ensuring deterministic sequences with a user-defined seed.

- **`rand_array(max, min)`**: Array with random integers in `[min, max]` and random dimensions.
  ```c
  ndarray_t arr = rand_array(20, 5);
  ```

- **`randu(rows, cols, seed)`**: Uniform random numbers in `[0, 1)`.
  ```c
  ndarray_t arr = randu(3, 3, 12345);
  ```

- **`randn(rows, cols, seed)`**: Normal (Gaussian) random numbers (μ=0, σ=1) via Box-Muller transform.
  ```c
  ndarray_t arr = randn(4, 4, 777);
  ```

- **`randint(rows, cols, max, min, seed)`**: Integer random numbers in `[min, max]`.
  ```c
  ndarray_t arr = randint(5, 5, 100, 10, 42);
  ```

- **`shuffle(&arr, seed)`**: Randomly shuffles an array's elements.
  ```c
  ndarray_t shuffled = shuffle(&arr, 99);
  ```

- **`randperm(n, seed)`**: Random permutation of integers `[0, n-1]`.
  ```c
  ndarray_t perm = randperm(10, 987);
  ```

### Trigonometric Functions

- **`nd_sin(&arr)`**, **`nd_cos(&arr)`**, **`nd_tan(&arr)`**: Apply trigonometric functions.
  ```c
  ndarray_t result = nd_sin(&arr);
  ```

- **`nd_sec(&arr)`**, **`nd_cosec(&arr)`**, **`nd_cot(&arr)`**: Secant, cosecant, cotangent.
  ```c
  ndarray_t result = nd_sec(&arr);
  ```

---

## ⚠️ Error Handling

NDMath provides robust error handling in `error.c`. Common errors include:
- **`null_error()`**: Null pointer detected.
- **`shape_error()`**: Invalid dimensions (e.g., zero rows/columns).
- **`dimension_error()`**: Invalid reshape dimensions.
- **`axis_error(axis)`**: Invalid axis (must be `"x"`, `"y"`, or `"all"`).
- **`zero_error()`**: Division by zero.
- **`malloc_error()`**: Memory allocation failure.

Errors print a message and exit the program. Example:
```
NULL POINTER ERROR
POINTER TO VOID PROVIDED
```

Use `isnull(&arr)` to check for null pointers before operations.

---

## 🔗 Integration in External Projects

NDMath can be integrated into external projects using three methods: static linking, dynamic linking, or direct source inclusion.

### 1. Static Linking (`libndmath.a`)
Static linking embeds the library into your binary, eliminating runtime dependencies.

**Steps**:
1. Build the static library:
   ```bash
   make static
   ```
   This creates `build/lib/libndmath.a`.

2. Include headers in your program:
   ```c
   #include <ndmath/array.h>
   #include <ndmath/random.h>
   #include <ndmath/helper.h>
   ```

3. Compile and link:
   ```bash
   gcc -Iinclude my_program.c -Lbuild/lib -lndmath -lm -o my_program
   ```

4. Run:
   ```bash
   ./my_program
   ```

### 2. Dynamic Linking (`libndmath.so`)
Dynamic linking allows library updates without recompiling your program.

**Steps**:
1. Build the shared library:
   ```bash
   make shared
   ```
   This creates `build/lib/libndmath.so`.

2. Include headers as above.

3. Compile and link:
   ```bash
   gcc -Iinclude my_program.c -Lbuild/lib -lndmath -lm -o my_program
   ```

4. Set the library path and run:
   ```bash
   export LD_LIBRARY_PATH=build/lib:$LD_LIBRARY_PATH
   ./my_program
   ```

5. (Optional) Install system-wide:
   ```bash
   make install DESTDIR=/usr/local
   sudo ldconfig
   ```

### 3. Direct Source Inclusion
Include NDMath source files directly in your project for simplicity.

**Steps**:
1. Copy the `src/` and `include/` directories into your project.
2. Include headers in your program.
3. Compile with all source files:
   ```bash
   gcc my_program.c src/*.c -Iinclude -lm -o my_program
   ```

### Makefile for External Projects
A sample `Makefile` for a project using NDMath:
```makefile
CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = -L./build/lib -lndmath -lm

SRC = my_program.c
OBJ = $(SRC:.c=.o)

all: my_program

my_program: $(OBJ)
	$(CC) $(OBJ) -o my_program $(CFLAGS) $(LDFLAGS)

clean:
	rm -f my_program *.o
```

**Directory Structure**:
```
my_project/
├── include/
│   ├── ndmath/
│   │   ├── array.h
│   │   ├── random.h
│   │   ├── ...
├── src/
│   ├── array.c
│   ├── random.c
│   ├── ...
├── build/
│   ├── lib/
│   │   ├── libndmath.a
│   │   ├── libndmath.so
├── my_program.c
├── Makefile
```

### Verifying the Library
Check if functions are available:
```bash
nm -g build/lib/libndmath.a | grep randu
# or
nm -D build/lib/libndmath.so | grep randu
```
Look for symbols like `randu`, `randn`, etc.

---

## 🧪 Testing

NDMath includes test files in the `tests/` directory (e.g., `test_rand.c`).

1. Build tests:
   ```bash
   make tests
   ```

2. Run tests:
   ```bash
   make run-tests
   ```
   This executes `build/bin/test_suite`.

To create custom tests:
1. Add a test file to `tests/` (e.g., `test_myfeature.c`).
2. Rebuild tests:
   ```bash
   make tests
   ```

---

## 📦 Example Program

Here's a comprehensive example demonstrating NDMath's capabilities:

```c
#include <ndmath/array.h>
#include <ndmath/operations.h>
#include <ndmath/io.h>
#include <ndmath/helper.h>
#include <ndmath/linalg.h>
#include <ndmath/statistics.h>
#include <ndmath/random.h>

int main() {
    // Create a 2x3 array
    ndarray_t arr = array(2, 3);
    arr.data[0][0] = 1; arr.data[0][1] = 2; arr.data[0][2] = 3;
    arr.data[1][0] = 4; arr.data[1][1] = 5; arr.data[1][2] = 6;
    printf("Original array:\n");
    print_array(arr, 2);

    // Save and load
    save_ndarray(&arr, "array.csv");
    ndarray_t loaded = load_ndarray("array.csv");
    printf("Loaded array:\n");
    print_array(loaded, 2);

    // Mathematical operations
    ndarray_t scaled = scaler(&arr, 2.0, '*');
    printf("Scaled array (x2):\n");
    print_array(scaled, 2);

    // Transpose
    ndarray_t transposed = transpose(&arr);
    printf("Transposed array:\n");
    print_array(transposed, 2);

    // Random array
    ndarray_t random = randu(2, 3, 12345);
    printf("Random array (uniform):\n");
    print_array(random, 2);

    // Statistics
    ndarray_t mean_val = mean(&arr, "all");
    printf("Mean of array:\n");
    print_array(mean_val, 2);

    // Clean up
    clean(&arr, &loaded, &scaled, &transposed, &random, &mean_val, NULL);
    return 0;
}
```

**Compile**:
```bash
make static
gcc -Iinclude example.c -Lbuild/lib -lndmath -lm -o example
```

**Run**:
```bash
./example
```

This program demonstrates array creation, file I/O, mathematical operations, random number generation, and statistics.

---

## 🔍 Troubleshooting

- **Compiler Errors**: Ensure all source files and headers are included. Use `-Iinclude` for headers.
- **Linker Errors**: Link with `-lndmath` and `-lm`. Verify library paths with `-Lbuild/lib`.
- **Segmentation Faults**: Check for null pointers or uninitialized arrays. Use `isnull(&arr)` and `clean()`.
- **File I/O Issues**: Ensure CSV files use semicolons (`;`) and correct paths.
- **Axis Errors**: Use valid axis values (`"x"`, `"y"`, `"all"`).
- **Memory Leaks**: Call `clean()` for every allocated array.

---

## 🤝 Contributing

To contribute:
1. Fork the repository (if available).
2. Create a new branch for your feature or bug fix.
3. Add tests in `tests/` and examples in `examples/`.
4. Submit a pull request with a clear description.

Report issues or suggest features via the repository's issue tracker.

---

## 🧹 Cleaning Up

Remove build artifacts:
```bash
make clean
```
This deletes the `build/` directory.

---

NDMath is a powerful yet accessible library for numerical computing in C. With this README, even beginners can set up, use, and extend NDMath for their projects. Happy coding! 🚀