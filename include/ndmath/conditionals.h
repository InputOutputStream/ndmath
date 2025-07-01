/**
 * @file conditionals.h
 * @brief Boolean condition checking functions for ndarray and image matrix structures
 * 
 * This header file provides a collection of boolean functions for testing various
 * conditions on ndarray_t and image_matrix_t structures. These functions are useful
 * for validation, error checking, and conditional logic in array and image processing
 * operations.
 * 
 * @author [Your Name]
 * @date [Date]
 * @version 1.0
 */

#ifndef CONDITIONALS
#define CONDITIONALS

#include "ndarray.h"

/* ========================================================================== */
/*                         NDARRAY CONDITION FUNCTIONS                       */
/* ========================================================================== */

/**
 * @brief Checks if an ndarray is square (equal number of rows and columns)
 * @param this Pointer to the ndarray to check
 * @return true if the array is square (rows == cols), false otherwise
 * @note A square array is necessary for certain mathematical operations like
 *       matrix inversion, eigenvalue computation, and determinant calculation
 * @warning Returns false if the array pointer is NULL
 * 
 * @code
 * ndarray_t arr = zeros(3, 3);
 * if (issquare(&arr)) {
 *     printf("Array is square - can compute determinant\n");
 * }
 * @endcode
 */
extern bool issquare(ndarray_t *this);

/**
 * @brief Checks if an ndarray is null or uninitialized
 * @param this Pointer to the ndarray to check
 * @return true if the array is null, uninitialized, or has null data pointer, false otherwise
 * @note This function is essential for defensive programming to avoid segmentation faults
 *       when working with potentially uninitialized arrays
 * @warning Always check arrays with this function before performing operations
 * 
 * @code
 * ndarray_t *arr = get_array_from_somewhere();
 * if (isnull(arr)) {
 *     fprintf(stderr, "Error: Array is null or uninitialized\n");
 *     return -1;
 * }
 * @endcode
 */
extern bool isnull(ndarray_t *this);

/**
 * @brief Checks if an ndarray has zero dimensions (empty shape)
 * @param this Pointer to the ndarray to check
 * @return true if either rows or columns (or both) are zero, false otherwise
 * @note An array with zero shape has no elements and cannot be used for most operations
 * @note This is different from isnull() - the array structure may be valid but have no dimensions
 * 
 * @code
 * ndarray_t empty_arr = array(0, 5);  // Zero rows
 * if (is_zero_shape(&empty_arr)) {
 *     printf("Array has zero dimensions - no elements to process\n");
 * }
 * @endcode
 */
extern bool is_zero_shape(ndarray_t *this);

/* ========================================================================== */
/*                      IMAGE MATRIX CONDITION FUNCTIONS                     */
/* ========================================================================== */

/**
 * @brief Checks if an image matrix has null or invalid row data
 * @param img Pointer to the image_matrix_t structure to check
 * @return true if the image matrix has null row data or invalid row structure, false otherwise
 * @note This function validates the row-wise structure of image matrices, which is
 *       crucial for image processing operations that iterate over rows
 * @warning Should be called before any row-based image processing operations
 * 
 * @code
 * image_matrix_t *image = load_image("photo.jpg");
 * if (is_null_matrix_row(image)) {
 *     fprintf(stderr, "Error: Image has invalid row structure\n");
 *     return -1;
 * }
 * @endcode
 */
extern bool is_null_matrix_row(image_matrix_t *img);

/**
 * @brief Checks if a specific column in an image matrix is null or invalid
 * @param img Pointer to the image_matrix_t structure to check
 * @param i Column index to validate (0-based indexing)
 * @return true if the specified column is null or invalid, false otherwise
 * @note This function is useful for validating specific columns before column-wise
 *       operations like vertical filtering, column extraction, or channel processing
 * @warning No bounds checking on column index - ensure 'i' is within valid range
 * 
 * @code
 * image_matrix_t *image = load_image("photo.jpg");
 * int col_to_process = 100;
 * if (is_null_matrix_col(image, col_to_process)) {
 *     fprintf(stderr, "Error: Column %d is invalid\n", col_to_process);
 *     return -1;
 * }
 * @endcode
 */
extern bool is_null_matrix_col(image_matrix_t *img, int i);

/**
 * @brief Checks if an entire image matrix is null or completely invalid
 * @param img Pointer to the image_matrix_t structure to check
 * @return true if the image matrix is null, uninitialized, or completely invalid, false otherwise
 * @note This is a comprehensive check that validates the overall structure of an image matrix
 * @note Should be the first validation performed on any image_matrix_t before processing
 * @warning This function should be called before any image processing operations to prevent
 *          segmentation faults and undefined behavior
 * 
 * @code
 * image_matrix_t *image = load_image("nonexistent.jpg");
 * if (is_null_matrix(image)) {
 *     fprintf(stderr, "Error: Failed to load image or image is invalid\n");
 *     cleanup_and_exit();
 * }
 * 
 * // Safe to proceed with image processing
 * apply_filter(image);
 * @endcode
 */
extern bool is_null_matrix(image_matrix_t *img);

#endif // !CONDITIONALS