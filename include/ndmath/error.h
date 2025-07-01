/**
 * @file error.h
 * @brief Error handling functions for ndarray operations
 * 
 * This header file contains function declarations for various error handling
 * routines used throughout the ndarray library. These functions typically
 * print error messages and may terminate the program or set error states.
 */

#ifndef ERROR
#define ERROR

#include "ndarray.h"

/**
 * @brief Handle axis-related errors
 * 
 * Reports an error when an invalid axis parameter is provided to an operation.
 * This typically occurs when specifying axes that don't exist in the array
 * or using invalid axis identifiers.
 * 
 * @param axis Pointer to string describing the problematic axis parameter
 * 
 * @pre axis should point to a valid null-terminated string
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void axis_error(char *axis);

/**
 * @brief Handle matrix operation errors
 * 
 * Reports errors related to invalid matrix operations, such as attempting
 * operations on incompatible matrix dimensions or non-matrix arrays.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void mat_error();

/**
 * @brief Handle division by zero errors
 * 
 * Reports errors when division by zero is attempted in array operations
 * or when zero values are encountered where non-zero values are required.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void zero_error();

/**
 * @brief Handle general memory allocation errors
 * 
 * Reports errors when memory allocation fails during array operations.
 * This is a general memory error handler that may be used in various
 * contexts throughout the library.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void memory_error(void);

/**
 * @brief Handle null pointer errors
 * 
 * Reports errors when a null pointer is encountered where a valid
 * pointer is expected. This is used for general null pointer validation.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void null_error();

/**
 * @brief Handle dimension mismatch errors during array reshaping
 * 
 * Reports errors when attempting to reshape an array to dimensions that
 * are incompatible with the original array's total element count or
 * when the new dimensions are invalid.
 * 
 * @param this Pointer to the ndarray being reshaped
 * @param new_cols Number of columns in the proposed new shape
 * @param new_rows Number of rows in the proposed new shape
 * 
 * @pre this should point to a valid ndarray structure or be NULL
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void dimension_error(ndarray_t *this, size_t new_cols, size_t new_rows);

/**
 * @brief Handle array indexing errors
 * 
 * Reports errors when attempting to access array elements using invalid
 * indices, such as out-of-bounds access or negative indices where not allowed.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void index_error();

/**
 * @brief Handle array shape errors
 * 
 * Reports errors related to incompatible array shapes in operations that
 * require specific shape relationships (e.g., broadcasting, concatenation).
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void shape_error();

/**
 * @brief Handle range validation errors
 * 
 * Reports errors when a value falls outside an expected range. Displays
 * the valid range bounds to help with debugging.
 * 
 * @param max Maximum allowed value (inclusive)
 * @param min Minimum allowed value (inclusive)
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void range_error(int max, int min);

/**
 * @brief Handle invalid array ordering errors
 * 
 * Reports errors when an invalid array ordering parameter is specified.
 * Common orderings include 'C' (row-major) and 'F' (column-major/Fortran).
 * 
 * @param order Pointer to string describing the invalid order parameter
 * 
 * @pre order should point to a valid null-terminated string
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void order_error(char *order);

/**
 * @brief Handle malloc-specific allocation errors
 * 
 * Reports errors specifically related to malloc() failures. This is a
 * more specific version of memory_error() for malloc operations.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void malloc_error();

/**
 * @brief Handle unexpected non-null pointer errors
 * 
 * Reports errors when a pointer is expected to be null but contains a
 * non-null value. This is the complement to null_error().
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void not_null_error();

/**
 * @brief Handle row/column specification errors
 * 
 * Reports errors when invalid row or column parameters are provided,
 * such as negative values or values exceeding array dimensions.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void row_col_error();

/**
 * @brief Handle null matrix data rows errors
 * 
 * Reports errors when matrix row data is unexpectedly null. This typically
 * occurs when accessing matrix rows that haven't been properly initialized
 * or have been freed.
 * 
 * @note This function may terminate the program or set a global error state
 */
extern void null_matrix_data_rows();

#endif // ERROR