#ifndef ARRAY
#define ARRAY

    #include "ndarray.h"

    extern ndarray_t array(size_t rows, size_t cols);
    extern ndarray_t linspace(int max, int min, double spacing, size_t rows ,size_t cols);
    extern ndarray_t arange(int max, int min, size_t rows, size_t cols, char *order);// on reflechis
    extern ndarray_t zeros(size_t rows, size_t cols);
    extern ndarray_t ones(size_t rows, size_t cols);
    extern ndarray_t empty(size_t rows, size_t cols);
    extern ndarray_t argmin(ndarray_t *this, char *axis);
    extern ndarray_t argmax(ndarray_t *this, char *axis);
    extern ndarray_t reshape(ndarray_t *this, size_t start, size_t stop);
    extern ndarray_t lower_triangle(double fill, size_t rows, size_t cols);
    extern ndarray_t upper_triangle(double fill, size_t rows, size_t cols);
    extern ndarray_t identity(size_t rows, size_t cols);
    extern ndarray_t copy(ndarray_t *arrayB);

    extern ndarray_t bindexing(ndarray_t *this, size_t start, size_t stop);
    extern ndarray_t cslice (ndarray_t *this, size_t col_start, size_t col_stop);
    extern ndarray_t rslice (ndarray_t *this, size_t rows_start, size_t rows_stop);
    extern ndarray_t cassign(ndarray_t *this, ndarray_t *arrayB, size_t send_col_index, size_t rec_col_index);
    extern ndarray_t rassign(ndarray_t *this, ndarray_t *arrayB, size_t send_row_index, size_t rec_row_index);

    extern ndarray_t repeat(ndarray_t *this, size_t cols);
    extern ndarray_t deepcopy(ndarray_t *src);
    extern ndarray_t flatten(ndarray_t *this);
    extern ndarray_t get_lines(ndarray_t *this, int *line_numbers, int number);
    extern void set(ndarray_t *this, size_t row, size_t col, double value);
    extern void fill(ndarray_t *this, double value);
    extern double get(ndarray_t *this, size_t row, size_t col);
    extern ndarray_t get_lines(ndarray_t *this, int *line_numbers, int number);
    extern ndarray_t row_index(ndarray_t *this, int row);

#endif