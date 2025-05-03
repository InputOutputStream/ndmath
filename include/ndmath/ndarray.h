#ifndef NDARRAY
#define NDARRAY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>

typedef struct ndarray
{
    size_t shape[3];  // Example: 2-dimensional array
    double** data;     // Example: Array of double values
    struct ndarray *next;
    size_t size;

} ndarray_t;

typedef struct dim
{
    size_t cols;
    size_t rows;
}dim_t;

#endif