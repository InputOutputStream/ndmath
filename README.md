# 📊 ndmath — Numerical Data Math Library

`ndmath` is a lightweight C library for numerical and statistical computations on array-based data structures. It provides foundational tools for array manipulation, linear algebra, probability, trigonometry, file I/O, and more — all organized around a core `ndarray` abstraction.

---

## 🚀 Features

- ✅ Typed 1D/2D array support (`ndarray`)
- 🔢 Basic and advanced statistics (mean, median, variance, etc.)
- ➗ Arithmetic operations on arrays and scalars
- 📁 CSV file input/output
- 🧠 Conditional logic and error handling
- 🎲 Random number generation
- 🧮 Linear algebra and trigonometric functions (WIP)
- 🧪 Test suite with modular organization

---

## 📁 Project Structure

```bash
.
├── include/ndmath/     # Public headers
├── src/                # Implementation files
├── examples/           # Example usage programs
├── tests/              # Unit test suite
├── build/              # Compiled output (bin/, obj/, lib/)
├── Makefile
└── README.md
```

---

## ⚙️ Build Instructions

> 📌 Prerequisites: `gcc`, `make`

From the root of the project:

```bash
make
```

This will:

- Compile the static and shared libraries in `build/lib/`
- Compile the test executable in `build/bin/test_suite`

---

## 🧪 Run Tests

```bash
./build/bin/test_suite
```

(You can add test cases in `tests/`.)

---

## 📦 Example Usage

```c
#include <ndmath/array.h>
#include <ndmath/statistics.h>

int main() {
    ndarray a = array(5, 5);
    printf("Mean: %f\n", mean(a, "all"));
    clean(&a);
    return 0;
}
```

You can compile it like this:

```bash
gcc -Iinclude -Lbuild/lib -lmathutils -o example examples/example1.c
```

---

## 🛠 Development Notes

- The library is under active development.
- Multi-dimensional (`n > 2`) support is planned.

---

## 📜 License

MIT License © Arnold Edu
