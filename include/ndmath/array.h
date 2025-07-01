/**
 * @file array.h
 * @brief N-dimensional array library interface for C
 * 
 * This header file provides a comprehensive interface for creating, manipulating,
 * and operating on multi-dimensional arrays (ndarray_t) in C. The library offers
 * functionality similar to NumPy arrays with operations for array creation,
 * indexing, slicing, and mathematical operations.
 * 
 * @author HGE
 * @date [Date]
 * @version 1.0
 */

#ifndef ARRAY
#define ARRAY

#include "ndarray.h"

/* ========================================================================== */
/*                           ARRAY CREATION FUNCTIONS                        */
/* ========================================================================== */

/**
 * @brief Creates an uninitialized ndarray with specified dimensions
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @return ndarray_t structure representing the created array
 * @note The array values are uninitialized and may contain garbage data
 */
extern ndarray_t array(size_t rows, size_t cols);

/**
 * @brief Creates an array with evenly spaced values over a specified interval
 * @param max Maximum value (inclusive)
 * @param min Minimum value (inclusive)
 * @param spacing Step size between consecutive values
 * @param rows Number of rows in the resulting array
 * @param cols Number of columns in the resulting array
 * @return ndarray_t containing evenly spaced values
 * @note Similar to NumPy's linspace function
 */
extern ndarray_t linspace(int max, int min, double spacing, size_t rows, size_t cols);

/**
 * @brief Creates an array with values in a specified range
 * @param max Maximum value (exclusive)
 * @param min Minimum value (inclusive)
 * @param rows Number of rows in the resulting array
 * @param cols Number of columns in the resulting array
 * @param order String specifying the fill order ("C" for row-major, "F" for column-major)
 * @return ndarray_t containing values in the specified range
 * @note Similar to NumPy's arange function
 */
extern ndarray_t arange(int max, int min, size_t rows, size_t cols, char *order);

/**
 * @brief Creates an array filled with zeros
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @return ndarray_t filled with zero values
 */
extern ndarray_t zeros(size_t rows, size_t cols);

/**
 * @brief Creates an array filled with ones
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @return ndarray_t filled with one values
 */
extern ndarray_t ones(size_t rows, size_t cols);

/**
 * @brief Creates an empty array with uninitialized values
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @return ndarray_t with allocated but uninitialized memory
 * @warning Values in the array are undefined and should be initialized before use
 */
extern ndarray_t empty(size_t rows, size_t cols);

/**
 * @brief Creates a lower triangular matrix filled with a specified value
 * @param fill Value to fill the lower triangle with
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @return ndarray_t representing a lower triangular matrix
 * @note Upper triangle elements are typically set to zero
 */
extern ndarray_t lower_triangle(double fill, size_t rows, size_t cols);

/**
 * @brief Creates an upper triangular matrix filled with a specified value
 * @param fill Value to fill the upper triangle with
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @return ndarray_t representing an upper triangular matrix
 * @note Lower triangle elements are typically set to zero
 */
extern ndarray_t upper_triangle(double fill, size_t rows, size_t cols);

/**
 * @brief Creates an identity matrix
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @return ndarray_t representing an identity matrix (1s on diagonal, 0s elsewhere)
 * @note For non-square matrices, only the main diagonal up to min(rows, cols) is filled with 1s
 */
extern ndarray_t identity(size_t rows, size_t cols);

/**
 * @brief Creates a shallow copy of an existing array
 * @param arrayB Pointer to the source array to copy
 * @return ndarray_t copy of the input array
 * @note This creates a new array structure but may share data with the original
 */
extern ndarray_t copy(ndarray_t *arrayB);

/**
 * @brief Creates a deep copy of an existing array
 * @param src Pointer to the source array to copy
 * @return ndarray_t independent copy with separate memory allocation
 * @note This creates a completely independent copy with its own memory
 */
extern ndarray_t deepcopy(ndarray_t *src);

/* ========================================================================== */
/*                           ARRAY ANALYSIS FUNCTIONS                        */
/* ========================================================================== */

/**
 * @brief Finds indices of minimum values along specified axis
 * @param this Pointer to the input array
 * @param axis String specifying the axis ("rows", "cols", or NULL for flattened array)
 * @return ndarray_t containing indices of minimum values
 * @note Returns indices, not the actual minimum values
 */
extern ndarray_t argmin(ndarray_t *this, char *axis);

/**
 * @brief Finds indices of maximum values along specified axis
 * @param this Pointer to the input array
 * @param axis String specifying the axis ("rows", "cols", or NULL for flattened array)
 * @return ndarray_t containing indices of maximum values
 * @note Returns indices, not the actual maximum values
 */
extern ndarray_t argmax(ndarray_t *this, char *axis);

/* ========================================================================== */
/*                           ARRAY MANIPULATION FUNCTIONS                    */
/* ========================================================================== */

/**
 * @brief Reshapes an array to new dimensions
 * @param this Pointer to the array to reshape
 * @param start New number of rows
 * @param stop New number of columns
 * @return ndarray_t with new shape but same data
 * @warning Total number of elements must remain the same (start * stop == original size)
 */
extern ndarray_t reshape(ndarray_t *this, size_t start, size_t stop);

/**
 * @brief Flattens a multi-dimensional array to a 1D array
 * @param this Pointer to the array to flatten
 * @return ndarray_t representing a 1D version of the input array
 * @note The resulting array will have dimensions (1, total_elements)
 */
extern ndarray_t flatten(ndarray_t *this);

/**
 * @brief Repeats an array along the column dimension
 * @param this Pointer to the array to repeat
 * @param cols Number of times to repeat the array horizontally
 * @return ndarray_t with repeated columns
 */
extern ndarray_t repeat(ndarray_t *this, size_t cols);

/* ========================================================================== */
/*                           INDEXING AND SLICING FUNCTIONS                  */
/* ========================================================================== */

/**
 * @brief Extracts a sub-array using boolean-like indexing
 * @param this Pointer to the source array
 * @param start Starting index
 * @param stop Ending index (exclusive)
 * @return ndarray_t containing elements from start to stop-1
 */
extern ndarray_t bindexing(ndarray_t *this, size_t start, size_t stop);

/**
 * @brief Extracts columns from an array (column slice)
 * @param this Pointer to the source array
 * @param col_start Starting column index (inclusive)
 * @param col_stop Ending column index (exclusive)
 * @return ndarray_t containing columns from col_start to col_stop-1
 */
extern ndarray_t cslice(ndarray_t *this, size_t col_start, size_t col_stop);

/**
 * @brief Extracts rows from an array (row slice)
 * @param this Pointer to the source array
 * @param rows_start Starting row index (inclusive)
 * @param rows_stop Ending row index (exclusive)
 * @return ndarray_t containing rows from rows_start to rows_stop-1
 */
extern ndarray_t rslice(ndarray_t *this, size_t rows_start, size_t rows_stop);

/**
 * @brief Extracts a single row from an array
 * @param this Pointer to the source array
 * @param row Index of the row to extract
 * @return ndarray_t containing the specified row
 */
extern ndarray_t row_index(ndarray_t *this, int row);

/**
 * @brief Extracts specific lines/rows from an array
 * @param this Pointer to the source array
 * @param line_numbers Array of line indices to extract
 * @param number Number of lines to extract
 * @return ndarray_t containing the specified lines
 */
extern ndarray_t get_lines(ndarray_t *this, int *line_numbers, int number);

/* ========================================================================== */
/*                           ASSIGNMENT FUNCTIONS                            */
/* ========================================================================== */

/**
 * @brief Assigns a column from one array to another array
 * @param this Pointer to the destination array
 * @param arrayB Pointer to the source array
 * @param send_col_index Column index in the source array
 * @param rec_col_index Column index in the destination array
 * @return ndarray_t with the column assignment completed
 * @note Modifies the destination array by copying a column from the source
 */
extern ndarray_t cassign(ndarray_t *this, ndarray_t *arrayB, size_t send_col_index, size_t rec_col_index);

/**
 * @brief Assigns a row from one array to another array
 * @param this Pointer to the destination array
 * @param arrayB Pointer to the source array
 * @param send_row_index Row index in the source array
 * @param rec_row_index Row index in the destination array
 * @return ndarray_t with the row assignment completed
 * @note Modifies the destination array by copying a row from the source
 */
extern ndarray_t rassign(ndarray_t *this, ndarray_t *arrayB, size_t send_row_index, size_t rec_row_index);

/* ========================================================================== */
/*                           ELEMENT ACCESS FUNCTIONS                        */
/* ========================================================================== */

/**
 * @brief Sets the value of a specific element in the array
 * @param this Pointer to the array to modify
 * @param row Row index of the element
 * @param col Column index of the element
 * @param value Value to set at the specified position
 * @warning No bounds checking - ensure indices are valid to avoid undefined behavior
 */
extern void set(ndarray_t *this, size_t row, size_t col, double value);

/**
 * @brief Gets the value of a specific element from the array
 * @param this Pointer to the array to access
 * @param row Row index of the element
 * @param col Column index of the element
 * @return double value at the specified position
 * @warning No bounds checking - ensure indices are valid to avoid undefined behavior
 */
extern double get(ndarray_t *this, size_t row, size_t col);

/**
 * @brief Fills the entire array with a specified value
 * @param this Pointer to the array to fill
 * @param value Value to fill the array with
 * @note Overwrites all existing values in the array
 */
extern void fill(ndarray_t *this, double value);

#endif