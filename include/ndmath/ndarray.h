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
    size_t shape[3];  // 2-dimensional array
    double** data;     // Array of double values
    struct ndarray *next;
    size_t size;

} ndarray_t;


typedef struct ndarray_data_loader
{
    size_t lines;
    size_t rows;
    double **data;
}ndarray_data_loader;


/*

#define IDX(i,j,ncols) ((i)*(ncols)+(j))

a.data[IDX(i,j,a.shape[1])]

*/

typedef struct {
    const char* name;
    ndarray_t* array;
} named_array_t;


typedef struct dim
{
    size_t cols;
    size_t rows;
}dim_t;

// Error handling struct
//To be implemented 
typedef enum {
    ND_SUCCESS,
    ND_SHAPE_ERROR,
    ND_INDEX_ERROR,
    ND_NULL_ERROR,
    ND_ALLOC_ERROR,
} nd_error_t;


#define TRACE() fprintf(stderr, "ERROR in function: %s\n", __func__)

#endif